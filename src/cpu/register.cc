#include "register.h"

#include "../util/log.h"

RegisterPair::RegisterPair(ByteRegister& high, ByteRegister& low) :
        low_byte(low),
        high_byte(high)
{
}

void RegisterPair::set_low(const uint8_t byte) {
    low_byte.set(byte);
}

void RegisterPair::set_high(const uint8_t byte) {
    high_byte.set(byte);
}

void RegisterPair::set_low(const ByteRegister& byte) {
    low_byte.set(byte.value());
}

void RegisterPair::set_high(const ByteRegister& byte) {
    low_byte.set(byte.value());
}

void RegisterPair::set(const uint16_t word) {
    /* Discard the upper byte */
    low_byte.set(static_cast<uint8_t>(word));

    /* Discard the lower byte */
    high_byte.set(static_cast<uint8_t>((word) >> 8));
}

uint8_t RegisterPair::low() const {
    return low_byte.value();
}

uint8_t RegisterPair::high() const {
    return high_byte.value();
}

uint16_t RegisterPair::value() const {
    return (high_byte.value() << 8) + low_byte.value();
}

void RegisterPair::increment() {
    set(value() + 1);
}

void RegisterPair::decrement() {
    set(value() - 1);
}
