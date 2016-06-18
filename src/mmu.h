#pragma once

#include "address.h"
#include "cartridge.h"

#include <cstdint>

class MMU {
public:
    MMU(Cartridge& cartridge);

    uint8_t read(const Address address) const;

    void write(const Address address, const uint8_t byte) const;
    void write_word(const Address address, const uint16_t word) const;

private:
    Cartridge& cartridge;

    bool boot_rom_loaded = true;
};
