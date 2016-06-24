#pragma once

#include "definitions.h"

class ByteRegister : Noncopyable {
public:
    ByteRegister() {}

    void set(const u8 new_value) { val = new_value; }
    u8 value() const { return val; }

    bool check_bit(u8 bit) const;
    void set_bit(u8 bit);
    void clear_bit(u8 bit);
    void set_bit_to(u8 bit, bool set);

    void increment() { val += 1; }
    void decrement() { val -= 1; }

private:
    u8 val;
};

class WordRegister : Noncopyable {
public:
    WordRegister() {}

    void set(const u16 new_value) { val = new_value; }
    u16 value() const { return val; }

    u8 low() const;
    u8 high() const;

    void increment() { val += 1; }
    void decrement() { val -= 1; }

private:
    u16 val;
};

class RegisterPair : Noncopyable {
public:
    RegisterPair(ByteRegister& high, ByteRegister& low);

    void set_low(const u8 byte);
    void set_high(const u8 byte);

    void set_low(const ByteRegister& byte);
    void set_high(const ByteRegister& byte);

    void set(const u16 word);

    u8 low() const;
    u8 high() const;

    u16 value() const;

    void increment();
    void decrement();

private:
    ByteRegister& low_byte;
    ByteRegister& high_byte;
};

class Offset {
public:
    Offset(u8 inVal) : val(inVal) {}
    Offset(ByteRegister& reg) : val(reg.value()) {}

    u8 value() { return val; }

private:
    u8 val;
};
