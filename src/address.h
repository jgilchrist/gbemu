#pragma once

#include "definitions.h"
#include "register.h"

class Address {
public:
    Address(u16 location);
    explicit Address(const RegisterPair& from);
    explicit Address(const WordRegister& from);

    u16 value() const;

    bool in_range(Address low, Address high) const;

    bool operator==(u16 other) const;
    Address operator+(uint other) const;
    Address operator-(uint other) const;

private:
    u16 addr = 0x0;
};
