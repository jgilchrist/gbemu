#include "address.h"

Address::Address(uint16_t location) : addr(location) {
}

Address::Address(RegisterPair from) : addr(from.value()) {
}

Address::Address(WordRegister from) : addr(from.value()) {
}

uint16_t Address::value() const {
    return addr;
}
