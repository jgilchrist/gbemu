#include "cartridge.h"

#include "../util/files.h"
#include "../util/log.h"

std::shared_ptr<Cartridge> get_cartridge(std::vector<u8> rom_data, std::vector<u8> ram_data) {
    log_info("Loaded %d KB", rom_data.size() / 1024);

    std::unique_ptr<CartridgeInfo> info = get_info(rom_data);

    switch (info->type) {
        case CartridgeType::ROMOnly:
            return std::make_shared<NoMBC>(rom_data, ram_data, std::move(info));
        case CartridgeType::MBC1:
            return std::make_shared<MBC1>(rom_data, ram_data, std::move(info));
        case CartridgeType::MBC2:
            fatal_error("MBC2 is unimplemented");
        case CartridgeType::MBC3:
            return std::make_shared<MBC3>(rom_data, ram_data, std::move(info));
        case CartridgeType::MBC4:
            fatal_error("MBC4 is unimplemented");
        case CartridgeType::MBC5:
            fatal_error("MBC5 is unimplemented");
        case CartridgeType::Unknown:
            fatal_error("Unknown cartridge type");
    }
}

Cartridge::Cartridge(
    std::vector<u8> rom_data,
    std::vector<u8> ram_data,
    std::unique_ptr<CartridgeInfo> in_cartridge_info
) :
    rom(std::move(rom_data)),
    cartridge_info(std::move(in_cartridge_info))
{
    auto ram_size_for_cartridge = get_actual_ram_size(cartridge_info->ram_size);

    if (ram_data.size() != 0) {
        if (ram_data.size() != ram_size_for_cartridge) { fatal_error("Invalid or corrupted RAM file. Read %d bytes, expected %d", ram_data.size(), ram_size_for_cartridge); }
        ram = ram_data;
    } else {
        ram = std::vector<u8>(ram_size_for_cartridge, 0);
    }
}

const std::vector<u8>& Cartridge::get_cartridge_ram() const {
    return ram;
}

NoMBC::NoMBC(
    std::vector<u8> rom_data,
    std::vector<u8> ram_data,
    std::unique_ptr<CartridgeInfo> in_cartridge_info
)
    : Cartridge(rom_data, ram_data, std::move(in_cartridge_info))
{
}

void NoMBC::write(const Address& address, u8 value) {
    log_warn("Attempting to write to cartridge ROM without an MBC");
    return;
}

u8 NoMBC::read(const Address& address) const {
    /* TODO: check this address is in sensible bounds */
    return rom.at(address.value());
}

MBC1::MBC1(
    std::vector<u8> rom_data,
    std::vector<u8> ram_data,
    std::unique_ptr<CartridgeInfo> in_cartridge_info
)
    : Cartridge(rom_data, ram_data, std::move(in_cartridge_info))
{
    rom_bank.set(0x1);
}

void MBC1::write(const Address& address, u8 value) {
    if (address.in_range(0x0000, 0x1FFF)) {
        ram_enabled = true;
    }

    if (address.in_range(0x2000, 0x3FFF)) {
        if (value == 0x0) { rom_bank.set(0x1); }

        if (value == 0x20) { rom_bank.set(0x21); return; }
        if (value == 0x40) { rom_bank.set(0x41); return; }
        if (value == 0x60) { rom_bank.set(0x61); return; }

        u16 rom_bank_bits = value & 0x1F;
        rom_bank.set(rom_bank_bits);
    }

    if (address.in_range(0x4000, 0x5FFF)) {
        log_unimplemented("Unimplemented: Setting upper bits of ROM bank number");
    }

    if (address.in_range(0x6000, 0x7FFF)) {
        log_unimplemented("Unimplemented: Selecting ROM/RAM Mode");
    }

    if (address.in_range(0xA000, 0xBFFF)) {
        if (!ram_enabled) { return; }

        auto offset_into_ram = 0x2000 * ram_bank.value();
        auto address_in_ram = (address - 0xA000) + offset_into_ram;
        ram.at(address_in_ram.value()) = value;
    }
}

u8 MBC1::read(const Address& address) const {
    if (address.in_range(0x0000, 0x3FFF)) {
        return rom.at(address.value());
    }

    if (address.in_range(0x4000, 0x7FFF)) {
        u16 address_into_bank = address.value() - 0x4000;
        uint bank_offset = 0x4000 * rom_bank.value();

        uint address_in_rom = bank_offset + address_into_bank;
        return rom.at(address_in_rom);
    }

    if (address.in_range(0xA000, 0xBFFF)) {
        auto offset_into_ram = 0x2000 * ram_bank.value();
        auto address_in_ram = (address - 0xA000) + offset_into_ram;
        return ram.at(address_in_ram.value());
    }
}

MBC3::MBC3(
    std::vector<u8> rom_data,
    std::vector<u8> ram_data,
    std::unique_ptr<CartridgeInfo> in_cartridge_info
)
    : Cartridge(rom_data, ram_data, std::move(in_cartridge_info))
{
    rom_bank.set(0x1);
}

void MBC3::write(const Address& address, u8 value) {
    if (address.in_range(0x0000, 0x1FFF)) {
        if (value == 0x0A) {
            ram_enabled = true;
        }

        if (value == 0x0) {
            ram_enabled = false;
        }
    }

    if (address.in_range(0x2000, 0x3FFF)) {
        if (value == 0x0) { rom_bank.set(0x1); }

        u16 rom_bank_bits = value & 0x7F;
        rom_bank.set(rom_bank_bits);
    }

    if (address.in_range(0x4000, 0x5FFF)) {
        if (value >= 0x0 && value <= 0x03) {
            ram_over_rtc = true;
            ram_bank.set(value);
        }

        if (value >= 0x08 && value <= 0xC) {
            ram_over_rtc = false;
            log_unimplemented("Using RTC registers of MBC3 cartridge");
        }
    }

    if (address.in_range(0x6000, 0x7FFF)) {
        log_unimplemented("Unimplemented: Latch clock data");
    }

    if (address.in_range(0xA000, 0xBFFF)) {
        if (!ram_enabled) { return; }

        if (ram_over_rtc) {
            auto offset_into_ram = 0x2000 * ram_bank.value();
            auto address_in_ram = (address - 0xA000) + offset_into_ram;
            ram.at(address_in_ram.value()) = value;
        }
    }
}

u8 MBC3::read(const Address& address) const {
    if (address.in_range(0x0000, 0x3FFF)) {
        return rom.at(address.value());
    }

    if (address.in_range(0x4000, 0x7FFF)) {
        u16 address_into_bank = address.value() - 0x4000;
        uint bank_offset = 0x4000 * rom_bank.value();

        uint address_in_rom = bank_offset + address_into_bank;
        return rom.at(address_in_rom);
    }

    if (address.in_range(0xA000, 0xBFFF)) {
        auto offset_into_ram = 0x2000 * ram_bank.value();
        auto address_in_ram = (address - 0xA000) + offset_into_ram;
        return ram.at(address_in_ram.value());
    }
}
