#ifndef EMULATOR_REGISTER_GROUP_H
#define EMULATOR_REGISTER_GROUP_H

#include <cstdint>

#include "register.h"

class RegisterGroup {
public:
    RegisterGroup(ByteRegister& low, ByteRegister& high);

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
