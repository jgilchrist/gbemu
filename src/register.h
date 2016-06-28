#pragma once

#include "definitions.h"

class ByteRegister : Noncopyable {
public:
    void set(const u8 new_value);
    void reset();
    u8 value() const;

    bool check_bit(u8 bit) const;
    void set_bit(u8 bit);
    void clear_bit(u8 bit);
    void set_bit_to(u8 bit, bool set);

    void increment();
    void decrement();

private:
    u8 val;
};

class WordRegister : Noncopyable {
public:
    void set(const u16 new_value);
    u16 value() const;

    u8 low() const;
    u8 high() const;

    void increment();
    void decrement();

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
