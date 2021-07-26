#pragma once

#include "cartridge_info.h"
#include "../address.h"
#include "../register.h"

#include <string>
#include <vector>
#include <memory>

class Cartridge {
public:
    Cartridge(
        std::vector<u8> rom_data,
        std::vector<u8> ram_data,
        std::unique_ptr<CartridgeInfo> cartridge_info
    );
    virtual ~Cartridge() = default;

    virtual auto read(const Address& address) const -> u8 = 0;
    virtual void write(const Address& address, u8 value) = 0;

    auto get_cartridge_ram() const -> const std::vector<u8>&;

protected:
    std::vector<u8> rom;
    std::vector<u8> ram;

    std::unique_ptr<CartridgeInfo> cartridge_info;
};

auto get_cartridge(std::vector<u8> rom_data, std::vector<u8> ram_data = {})
    -> std::shared_ptr<Cartridge>;

class NoMBC : public Cartridge {
public:
    NoMBC(
        std::vector<u8> rom_data,
        std::vector<u8> ram_data,
        std::unique_ptr<CartridgeInfo> cartridge_info
    );

    auto read(const Address& address) const -> u8 override;
    void write(const Address& address, u8 value) override;
};

class MBC1 : public Cartridge {
public:
    MBC1(
        std::vector<u8> rom_data,
        std::vector<u8> ram_data,
        std::unique_ptr<CartridgeInfo> cartridge_info
    );

    auto read(const Address& address) const -> u8 override;
    void write(const Address& address, u8 value) override;

private:
    WordRegister rom_bank;
    WordRegister ram_bank;
    bool ram_enabled = false;

    // TODO: ROM/RAM Mode Select (6000-7FFF)
    // This 1bit Register selects whether the two bits of the above register should
    // be used as upper two bits of the ROM Bank, or as RAM Bank Number.
    bool rom_banking_mode = true;
};

class MBC3 : public Cartridge {
public:
    MBC3(
        std::vector<u8> rom_data,
        std::vector<u8> ram_data,
        std::unique_ptr<CartridgeInfo> cartridge_info
    );

    auto read(const Address& address) const -> u8 override;
    void write(const Address& address, u8 value) override;

private:
    WordRegister rom_bank;
    WordRegister ram_bank;
    bool ram_enabled = false;
    bool ram_over_rtc = true;

    // TODO: ROM/RAM Mode Select (6000-7FFF)
    // This 1bit Register selects whether the two bits of the above register should
    // be used as upper two bits of the ROM Bank, or as RAM Bank Number.
    bool rom_banking_mode = true;
};
