#ifndef EMULATOR_ADDRESS_H
#define EMULATOR_ADDRESS_H

#include <cstdint>
#include "cpu/register.h"

class Address {
public:
    explicit Address(uint16_t location);
    explicit Address(RegisterPair from);
    explicit Address(WordRegister from);

    uint16_t value() const;

private:
    uint16_t addr;
};

#endif
