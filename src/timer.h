#pragma once

#include "definitions.h"
#include "register.h"

class CPU;

class Timer {
public:
    Timer(CPU& cpu);

    void tick(uint cycles);

    u8 get_divider() const;
    u8 get_timer() const;
    u8 get_timer_modulo() const;
    u8 get_timer_control() const;

    void reset_divider();
    void set_timer(u8 value);
    void set_timer_modulo(u8 value);
    void set_timer_control(u8 value);

private:
    uint ticks_needed_to_increment();

    uint timer_logical_ticks = 0;

    CPU& cpu;

    ByteRegister divider;
    ByteRegister timer_counter;

    ByteRegister timer_modulo;
    ByteRegister timer_control;
};
