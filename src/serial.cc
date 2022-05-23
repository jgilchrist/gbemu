#include "serial.h"

#include "util/bitwise.h"
#include "util/log.h"

#include <cstdio>

void Serial::register_get_data_callback(const get_serial_data_callback_t& _serial_data_callback) {
    get_serial_data_callback = _serial_data_callback;
}

auto Serial::read() const -> u8 {
    return get_serial_data_callback();
}

void Serial::write(const u8 byte) {
    data = byte;
}

void Serial::write_control(const u8 byte) const {
    if (bitwise::check_bit(byte, 7) && options.print_serial) {
        printf("%c", data);
        fflush(stdout);
    }
}
