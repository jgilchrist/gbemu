#include "timer.h"

#include "definitions.h"
#include "cpu/cpu.h"
#include "util/bitwise.h"

Timer::Timer(CPU& inCpu) : cpu(inCpu) {
    log_info("%d", CLOCK_RATE / 4096);
    log_info("%d", CLOCK_RATE / 262144);
    log_info("%d", CLOCK_RATE / 65536);
    log_info("%d", CLOCK_RATE / 16384);
}

void Timer::tick(uint cycles) {
    u8 new_divider = static_cast<u8>(divider.value() + cycles);
    divider.set(new_divider);

    auto timer_is_on = timer_control.check_bit(2);
    if (timer_is_on == 0) { return; }

    timer_total_ticks += cycles;
    timer_logical_ticks += cycles;
    auto tick_limit = ticks_needed_to_increment();

    if (timer_logical_ticks >= tick_limit) {
        timer_logical_ticks = timer_logical_ticks % tick_limit;

        u8 old_timer_counter = timer_counter.value();
        timer_counter.increment();
        log_info("%02X %d", timer_counter.value(), timer_logical_ticks);
        if (timer_counter.value() < old_timer_counter) {
            log_info("Setting interrupt %d %d", tick_limit, timer_total_ticks);
            cpu.interrupt_flag.set_bit_to(2, true);
            timer_counter.set(timer_modulo.value());
        }
    } else {
        log_info("%02X %d", timer_counter.value(), timer_logical_ticks);
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

    // Mask the bottom two bits of the TAC
    u8 timer_value = timer_control.value() & 0x3;

    switch (timer_value) {
        case 0: return CLOCK_RATE / 4096;
        case 1: return CLOCK_RATE / 262144;
        case 2: return CLOCK_RATE / 65536;
        case 3: return CLOCK_RATE / 16384;
        default: fatal_error("Invalid calculation in timer");
    }
}
