#include "register.h"

#include "util/bitwise.h"
#include "util/log.h"

ByteRegister::ByteRegister(bool _is_flags) : is_flags(_is_flags) {
}

void ByteRegister::set(const u8 new_value) {
    val = new_value;

    if (is_flags) { val = val & 0xF0; }
}

void ByteRegister::reset() {
    val = 0;
}

u8 ByteRegister::value() const {
    return val;
}

bool ByteRegister::check_bit(u8 bit) const {
    return bitwise::check_bit(val, bit);
}

void ByteRegister::set_bit(u8 bit) {
    val = bitwise::set_bit(val, bit);
}

void ByteRegister::clear_bit(u8 bit) {
    val = bitwise::clear_bit(val, bit);
}

void ByteRegister::set_bit_to(u8 bit, bool set) {
    val = bitwise::set_bit_to(val, bit, set);
}

void ByteRegister::increment() {
    val += 1;
}
void ByteRegister::decrement() {
    val -= 1;
}

bool ByteRegister::operator==(u8 other) const {
    return val == other;
}


void WordRegister::set(const u16 new_value) {
    val = new_value;
}
u16 WordRegister::value() const {
    return val;
}

u8 WordRegister::low() const {
    return static_cast<u8>(val);
}

u8 WordRegister::high() const {
    return static_cast<u8>((val) >> 8);
}

void WordRegister::increment() {
    val += 1;
}
void WordRegister::decrement() {
    val -= 1;
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
    return bitwise::compose_bytes(high_byte.value(), low_byte.value());
}

void RegisterPair::increment() {
    set(value() + 1);
}

void RegisterPair::decrement() {
    set(value() - 1);
}
