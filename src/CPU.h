#ifndef EMULATOR_CPU_H
#define EMULATOR_CPU_H

#include <cstdint>
#include "Clock.h"
#include "MMU.h"

/**
 * The Gameboy CPU is a Z80 (8-bit) chip.
 */

class CPU {
public:
    CPU();

    void execute_opcode(const uint8_t opcode);

private:
    Clock clock;
    MMU mmu;

    /* Basic registers */
    uint8_t a, b, c, d, e, h, l;

    /* Special purpose registers */

    /*
     * Flags set dependant on the result of the last operation
     *  0x80 - produced 0
     *  0x40 - was a subtraction
     *  0x20 - lower half of the byte overflowed 15
     *  0x10 - overflowed 255 or underflowed 0 for additions/subtractions
     */
    uint8_t f;

    /* Program counter */
    uint16_t pc;

    /* Stack pointer */
    uint16_t sp;
};

#endif
