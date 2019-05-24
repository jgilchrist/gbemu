#pragma once

#include "definitions.h"
#include "register.h"

class Gameboy;

class Timer {
public:
    Timer(Gameboy& inGb);

    void tick(uint cycles);

    auto get_divider() const -> u8;
    auto get_timer() const -> u8;
    auto get_timer_modulo() const -> u8;
    auto get_timer_control() const -> u8;

    void reset_divider();
    void set_timer(u8 value);
    void set_timer_modulo(u8 value);
    void set_timer_control(u8 value);

private:
    uint ticks_needed_to_increment();

    uint timer_logical_ticks = 0;
    uint timer_total_ticks = 0;

    Gameboy& gb;

    ByteRegister divider;
    ByteRegister timer_counter;

    ByteRegister timer_modulo;
    ByteRegister timer_control;
};
