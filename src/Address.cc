#include "Address.h"

Address::Address() : addr(0) {
}

Address::Address(uint16_t location) : addr(location) {
}

Address::Address(RegisterGroup from) : addr(from.value()) {
}

uint16_t Address::value() const {
    return addr;
}
