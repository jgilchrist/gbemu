#pragma once

#include "definitions.h"
#include "register.h"

class Address {
public:
    Address(u16 location);
    explicit Address(const RegisterPair& from);
    explicit Address(const WordRegister& from);

    auto value() const -> u16;

    auto in_range(Address low, Address high) const -> bool;

    auto operator==(u16 other) const -> bool;
    auto operator+(uint other) const -> Address;
    auto operator-(uint other) const -> Address;

private:
    u16 addr = 0x0;
};
