#ifndef EMULATOR_MMU_H
#define EMULATOR_MMU_H

#include <cstdint>
#include "Memory.h"

class MMU {
public:
    MMU();

    uint8_t read_byte(const uint16_t address) const;
    uint8_t read_word(const uint16_t address) const;

    void write_byte(const uint16_t address, const uint16_t byte) const;
    void write_word(const uint16_t address, const uint16_t byte) const;

private:
    Memory memory;
};

#endif
