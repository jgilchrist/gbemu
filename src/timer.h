#pragma once

#include "definitions.h"
#include "register.h"

class Timer {
public:
    void tick(uint cycles);

    u8 get_divider() const;
    u8 get_timer() const;
    u8 get_timer_modulo() const;
    u8 get_timer_control() const;

    void reset_divider();
    void set_timer_modulo(u8 value);
    void set_timer_control(u8 value);

private:
    ByteRegister divider;
    ByteRegister timer_counter;

    ByteRegister timer_modulo;
    ByteRegister timer_control;
};
