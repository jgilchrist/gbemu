#pragma once

#include "definitions.h"
#include "register.h"

class Address {
public:
    Address(u16 location);
    explicit Address(RegisterPair& from);
    explicit Address(WordRegister& from);

    u16 value() const;

    bool in_range(Address low, Address high) const;

private:
    u16 addr;
};
