#include "timer.h"

#include "definitions.h"
#include "cpu/cpu.h"
#include "util/bitwise.h"

Timer::Timer(CPU& inCpu) : cpu(inCpu) {
}

void Timer::tick(uint cycles) {
    u8 new_divider = static_cast<u8>(divider.value() + cycles);
    divider.set(new_divider);

    auto timer_is_on = timer_control.check_bit(2);
    if (timer_is_on == 0) { return; }

    timer_logical_ticks += 1;
    auto tick_limit = ticks_needed_to_increment();

    if (timer_logical_ticks >= tick_limit) {
        timer_counter.increment();
        timer_logical_ticks = 0;

        if (timer_counter.value() == 0) {
            log_info("Setting interrupt");
            cpu.interrupt_flag.set_bit_to(interrupts::timer, true);
            timer_counter.set(timer_modulo.value());
        }
    }
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

void Timer::set_timer(u8 value) {
    timer_counter.set(value);
}

void Timer::set_timer_modulo(u8 value) {
    timer_modulo.set(value);
}

void Timer::set_timer_control(u8 value) {
    timer_control.set(value);
}

uint Timer::ticks_needed_to_increment() {
    using bitwise::check_bit;

    bool bit_0 = timer_control.check_bit(0);
    bool bit_1 = timer_control.check_bit(1);

    uint bits = bit_0 + bit_1;

    switch (bits) {
        case 0: return CLOCK_RATE / 4096;
        case 1: return CLOCK_RATE / 262144;
        case 2: return CLOCK_RATE / 65536;
        case 3: return CLOCK_RATE / 16384;
        default: fatal_error("Invalid calculation in timer");
    }
}
