#include "address.h"

Address::Address(u16 location) : addr(location) {
}

Address::Address(const RegisterPair& from) : addr(from.value()) {
}

Address::Address(const WordRegister& from) : addr(from.value()) {
}

auto Address::value() const -> u16 { return addr; }

auto Address::in_range(Address low, Address high) const -> bool {
    return low.value() <= value() && value() <= high.value();
}

auto Address::operator==(u16 other) const -> bool { return addr == other; }

auto Address::operator+(uint other) const -> Address {
    u16 new_addr = static_cast<u16>(addr + other);
    return Address{new_addr};
}

auto Address::operator-(uint other) const -> Address {
    u16 new_addr = static_cast<u16>(addr - other);
    return Address{new_addr};
}
