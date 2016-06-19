#pragma once

#include "address.h"
#include "cartridge.h"

class MMU {
public:
    MMU(Cartridge& cartridge);

    u8 read(const Address address) const;

    void write(const Address address, const u8 byte) const;
    void write_word(const Address address, const u16 word) const;

    bool boot_rom_active() const;

private:
    Cartridge& cartridge;
};
