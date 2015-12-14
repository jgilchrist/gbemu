#ifndef EMULATOR_ADDRESS_H
#define EMULATOR_ADDRESS_H

#include <cstdint>
#include "RegisterGroup.h"

class Address {
public:
    Address();
    Address(uint16_t location);
    Address(RegisterGroup from);
    Address(WordRegister from);

    uint16_t value() const;

private:
    uint16_t addr;
};

#endif
