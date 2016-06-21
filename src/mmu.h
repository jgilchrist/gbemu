#pragma once

#include "address.h"
#include "cartridge.h"

#include <vector>

class MMU {
public:
    MMU(Cartridge& cartridge);

    u8 read(const Address address) const;

    void write(const Address address, const u8 byte);
    void write_word(const Address address, const u16 word);

private:
    bool boot_rom_active() const;

    u8 read_io(const Address address) const;
    void write_io(const Address address, const u8 byte);

    u8 memory_read(const Address address) const;
    void memory_write(const Address address, const u8 byte);

    Cartridge& cartridge;
    std::vector<u8> memory;
};
