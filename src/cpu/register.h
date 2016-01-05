#ifndef EMULATOR_REGISTER_H
#define EMULATOR_REGISTER_H

#include <cstdint>

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

using ByteRegister = Register<uint8_t>;
using WordRegister = Register<uint16_t>;

class RegisterPair {
public:
    RegisterPair(ByteRegister& low, ByteRegister& high);

    void set_low(const uint8_t byte);
    void set_high(const uint8_t byte);

    void set_low(const ByteRegister& byte);
    void set_high(const ByteRegister& byte);

    void set(const uint16_t word);

    uint8_t low() const;
    uint8_t high() const;

    uint16_t value() const;

    void increment();
    void decrement();

private:
    ByteRegister& low_byte;
    ByteRegister& high_byte;
};

class Offset {
public:
    Offset(uint8_t val) : val(val) {};
    Offset(ByteRegister& reg) : val(reg.value()) {};

    uint8_t value() { return val; }

private:
    uint8_t val;
};

#endif
