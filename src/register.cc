#include "register.h"

#include "util/bitwise.h"

void ByteRegister::set(const u8 new_value) {
    val = new_value;
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


void FlagRegister::set(const u8 new_value) {
    val = new_value & 0xF0;
}

void FlagRegister::set_flag_zero(bool set) {
    set_bit_to(7, set);
}

void FlagRegister::set_flag_subtract(bool set) {
    set_bit_to(6, set);
}

void FlagRegister::set_flag_half_carry(bool set) {
    set_bit_to(5, set);
}

void FlagRegister::set_flag_carry(bool set) {
    set_bit_to(4, set);
}

bool FlagRegister::flag_zero() const {
    return check_bit(7);
}

bool FlagRegister::flag_subtract() const {
    return check_bit(6);
}

bool FlagRegister::flag_half_carry() const {
    return check_bit(5);
}

bool FlagRegister::flag_carry() const {
    return check_bit(4);
}

u8 FlagRegister::flag_zero_value() const {
    return static_cast<u8>(flag_zero() ? 1 : 0);
}

u8 FlagRegister::flag_subtract_value() const {
    return static_cast<u8>(flag_subtract() ? 1 : 0);
}

u8 FlagRegister::flag_half_carry_value() const {
    return static_cast<u8>(flag_half_carry() ? 1 : 0);
}

u8 FlagRegister::flag_carry_value() const {
    return static_cast<u8>(flag_carry() ? 1 : 0);
}
