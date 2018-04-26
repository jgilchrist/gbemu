#include "serial.h"

#include "util/bitwise.h"
#include "util/log.h"

#include <cstdio>

u8 Serial::read() const {
    return data;
}

void Serial::write(const u8 byte) {
    data = byte;
}

void Serial::write_control(const u8 byte) {
    if (bitwise::check_bit(byte, 7) && should_print) {
        printf("%c", data);
        fflush(stdout);
    }
}
