#include "timer.h"

void Timer::tick(u8 cycles) {
    divider.set(divider.value() + cycles);
}

u8 Timer::get_divider() const {
    return divider.value();
}

u8 Timer::get_timer() const {
    return timer_counter.value();
}

u8 Timer::get_timer_modulo() const {
    return timer_modulo.value();
}

u8 Timer::get_timer_control() const {
    return timer_control.value();
}

void Timer::reset_divider() {
    divider.set(0x0);
}

void Timer::set_timer_modulo(u8 value) {
}

void Timer::set_timer_control(u8 value) {
}
