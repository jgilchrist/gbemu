#include "address.h"

Address::Address(u16 location) : addr(location) {
}

Address::Address(const RegisterPair& from) : addr(from.value()) {
}

Address::Address(const WordRegister& from) : addr(from.value()) {
}

u16 Address::value() const {
    return addr;
}

bool Address::in_range(Address low, Address high) const {
    return low.value() <= value() && value() <= high.value();
}

bool Address::operator==(u16 other) const {
    return addr == other;
}

Address Address::operator+(uint other) const {
    u16 new_addr = static_cast<u16>(addr + other);
    return Address(new_addr);
}

Address Address::operator-(uint other) const {
    u16 new_addr = static_cast<u16>(addr - other);
    return Address(new_addr);
}
