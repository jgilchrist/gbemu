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

    virtual u8 read(const Address& address) const = 0;
    virtual void write(const Address& address, u8 value) = 0;

    const std::vector<u8>& get_cartridge_ram() const;

protected:
    std::vector<u8> rom;
    std::vector<u8> ram;

    std::unique_ptr<CartridgeInfo> cartridge_info;
};

std::shared_ptr<Cartridge> get_cartridge(std::vector<u8> rom_data, std::vector<u8> ram_data = {});

class NoMBC : public Cartridge {
public:
    NoMBC(
        std::vector<u8> rom_data,
        std::vector<u8> ram_data,
        std::unique_ptr<CartridgeInfo> cartridge_info
    );

    u8 read(const Address& address) const override;
    void write(const Address& address, u8 value) override;
};

class MBC1 : public Cartridge {
public:
    MBC1(
        std::vector<u8> rom_data,
        std::vector<u8> ram_data,
        std::unique_ptr<CartridgeInfo> cartridge_info
    );

    u8 read(const Address& address) const override;
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

    u8 read(const Address& address) const override;
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
