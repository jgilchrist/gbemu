#ifndef EMULATOR_REGISTER_GROUP_H
#define EMULATOR_REGISTER_GROUP_H

#include <cstdint>

#include "Register.h"

class RegisterGroup {
public:
    RegisterGroup(Register& x, Register& y);

    void set_low(const uint8_t byte);
    void set_high(const uint8_t byte);

    void set(const uint16_t word);

    uint8_t low() const;
    uint8_t high() const;

    uint16_t value() const;

    void increment();
    void decrement();

private:
    Register& low_byte;
    Register& high_byte;
};

#endif
