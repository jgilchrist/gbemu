#ifndef EMULATOR_REGISTER_H
#define EMULATOR_REGISTER_H

#include <cstdint>

class Register {
public:
    Register();

    void set(const uint8_t byte);
    uint8_t value();

    void increment();
    void decrement();

private:
    uint8_t val;
};

#endif
