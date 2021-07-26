#include "serial.h"

#include "util/bitwise.h"
#include "util/log.h"

#include <cstdio>

auto Serial::read() const -> u8 { return data; }

void Serial::write(const u8 byte) {
    data = byte;
}

void Serial::write_control(const u8 byte) const {
    if (bitwise::check_bit(byte, 7) && options.print_serial) {
        printf("%c", data);
        fflush(stdout);
    }
}
