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

#endif
