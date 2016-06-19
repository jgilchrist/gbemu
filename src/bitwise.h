#pragma once

#include "definitions.h"
#include "util/log.h"

inline u16 compose_bytes(const u8 high, const u8 low) {
    return (high << 8) + low;
}

inline bool check_bit(const u8 value, const int bit) {
    return (value & (1 << bit)) != 0;
}

inline u8 set_bit(const u8 value, const int bit) {
    return value | (1 << bit);
}

inline u8 clear_bit(const u8 value, const int bit) {
    return value & ~(1 << bit);
}

inline u8 set_bit_to(const u8 value, const int bit, bool bit_on) {
    if (bit_on) {
        return set_bit(value, bit);
    } else {
        return clear_bit(value, bit);
    }
}
