#ifndef EMULATOR_MMU_H
#define EMULATOR_MMU_H

#include <cstdint>
#include "Memory.h"
#include "Address.h"

class MMU {
public:
    MMU();

    uint8_t read_byte(const Address address) const;
    uint16_t read_word(const Address address) const;

    void write_byte(const Address address, const uint8_t byte) const;
    void write_word(const Address address, const uint16_t word) const;

private:
    Memory memory;
};

#endif
