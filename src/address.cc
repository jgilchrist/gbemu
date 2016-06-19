#include "address.h"

Address::Address(u16 location) : addr(location) {
}

Address::Address(RegisterPair from) : addr(from.value()) {
}

Address::Address(WordRegister from) : addr(from.value()) {
}

u16 Address::value() const {
    return addr;
}

bool Address::in_range(Address low, Address high) const {
    return low.value() <= value() && value() <= high.value();
}
