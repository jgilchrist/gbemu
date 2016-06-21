#include "register.h"

#include "util/bitwise.h"
#include "util/log.h"

u8 WordRegister::low() const {
    return static_cast<u8>(val);
}

u8 WordRegister::high() const {
    return static_cast<u8>((val) >> 8);
}

RegisterPair::RegisterPair(ByteRegister& high, ByteRegister& low) :
        low_byte(low),
        high_byte(high)
{
}

void RegisterPair::set_low(const u8 byte) {
    low_byte.set(byte);
}

void RegisterPair::set_high(const u8 byte) {
    high_byte.set(byte);
}

void RegisterPair::set_low(const ByteRegister& byte) {
    low_byte.set(byte.value());
}

void RegisterPair::set_high(const ByteRegister& byte) {
    low_byte.set(byte.value());
}

void RegisterPair::set(const u16 word) {
    /* Discard the upper byte */
    low_byte.set(static_cast<u8>(word));

    /* Discard the lower byte */
    high_byte.set(static_cast<u8>((word) >> 8));
}

u8 RegisterPair::low() const {
    return low_byte.value();
}

u8 RegisterPair::high() const {
    return high_byte.value();
}

u16 RegisterPair::value() const {
    return compose_bytes(high_byte.value(), low_byte.value());
}

void RegisterPair::increment() {
    set(value() + 1);
}

void RegisterPair::decrement() {
    set(value() - 1);
}
