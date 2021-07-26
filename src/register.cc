#include "register.h"

#include "util/bitwise.h"

void ByteRegister::set(const u8 new_value) {
    val = new_value;
}

void ByteRegister::reset() {
    val = 0;
}

auto ByteRegister::value() const -> u8 { return val; }

auto ByteRegister::check_bit(u8 bit) const -> bool { return bitwise::check_bit(val, bit); }

void ByteRegister::set_bit_to(u8 bit, bool set) {
    val = bitwise::set_bit_to(val, bit, set);
}

void ByteRegister::increment() {
    val += 1;
}
void ByteRegister::decrement() {
    val -= 1;
}

auto ByteRegister::operator==(u8 other) const -> bool { return val == other; }


void WordRegister::set(const u16 new_value) {
    val = new_value;
}
auto WordRegister::value() const -> u16 { return val; }

auto WordRegister::low() const -> u8 { return static_cast<u8>(val); }

auto WordRegister::high() const -> u8 { return static_cast<u8>((val) >> 8); }

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

auto RegisterPair::low() const -> u8 { return low_byte.value(); }

auto RegisterPair::high() const -> u8 { return high_byte.value(); }

auto RegisterPair::value() const -> u16 {
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

auto FlagRegister::flag_zero() const -> bool { return check_bit(7); }

auto FlagRegister::flag_subtract() const -> bool { return check_bit(6); }

auto FlagRegister::flag_half_carry() const -> bool { return check_bit(5); }

auto FlagRegister::flag_carry() const -> bool { return check_bit(4); }

auto FlagRegister::flag_zero_value() const -> u8 { return static_cast<u8>(flag_zero() ? 1 : 0); }

auto FlagRegister::flag_subtract_value() const -> u8 {
    return static_cast<u8>(flag_subtract() ? 1 : 0);
}

auto FlagRegister::flag_half_carry_value() const -> u8 {
    return static_cast<u8>(flag_half_carry() ? 1 : 0);
}

auto FlagRegister::flag_carry_value() const -> u8 { return static_cast<u8>(flag_carry() ? 1 : 0); }
