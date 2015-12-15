#include "RegisterGroup.h"

RegisterGroup::RegisterGroup(ByteRegister& low, ByteRegister& high) :
        low_byte(low),
        high_byte(high)
{
}

void RegisterGroup::set_low(const uint8_t byte) {
    low_byte.set(byte);
}

void RegisterGroup::set_high(const uint8_t byte) {
    high_byte.set(byte);
}

void RegisterGroup::set_low(const ByteRegister& byte) {
    low_byte.set(byte.value());
}

void RegisterGroup::set_high(const ByteRegister& byte) {
    low_byte.set(byte.value());
}

void RegisterGroup::set(const uint16_t word) {
    /* Discard the upper byte */
    low_byte.set(static_cast<uint8_t>(word));

    /* Discard the lower byte */
    high_byte.set(static_cast<uint8_t>((word) >> 8));
}

uint8_t RegisterGroup::low() const {
    return low_byte.value();
}

uint8_t RegisterGroup::high() const {
    return high_byte.value();
}

uint16_t RegisterGroup::value() const {
    return (high_byte.value() << 8) + low_byte.value();
}

void RegisterGroup::increment() {
    set(value() + 1);
}

void RegisterGroup::decrement() {
    set(value() - 1);
}
