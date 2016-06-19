#pragma once

#include "../definitions.h"

template <typename T>
class Register {
public:
    Register() {};

    void set(const T new_value) { val = new_value; };
    T value() const { return val; };

    void increment() { val += 1; };
    void decrement() { val -= 1; };

private:
    T val;
};

using ByteRegister = Register<u8>;
using WordRegister = Register<u16>;

class RegisterPair {
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
    Offset(u8 val) : val(val) {};
    Offset(ByteRegister& reg) : val(reg.value()) {};

    u8 value() { return val; }

private:
    u8 val;
};
