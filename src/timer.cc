#include "timer.h"

void Timer::tick(uint cycles) {
    u8 new_divider = static_cast<u8>(divider.value() + cycles);
    divider.set(new_divider);
}

auto Timer::get_divider() const -> u8 { return divider.value(); }

auto Timer::get_timer() const -> u8 { return timer_counter.value(); }

auto Timer::get_timer_modulo() const -> u8 { return timer_modulo.value(); }

auto Timer::get_timer_control() const -> u8 { return timer_control.value(); }

void Timer::reset_divider() {
    divider.set(0x0);
}

void Timer::set_timer_modulo(u8 value) {
}

void Timer::set_timer_control(u8 value) {
}
