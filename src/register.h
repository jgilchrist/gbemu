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

typedef Register<uint8_t> ByteRegister;
typedef Register<uint16_t> WordRegister;

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

#endif
