#pragma once

#include "util/log.h"

#include <cstdint>

inline uint16_t compose_bytes(const uint8_t low, const uint8_t high) {
    return (high << 8) + low;
}

inline bool check_bit(const uint8_t value, const int bit) {
    return (value & (1 << bit)) != 0;
}

inline uint8_t set_bit(const uint8_t value, const int bit) {
    return value | (1 << bit);
}

inline uint8_t clear_bit(const uint8_t value, const int bit) {
    return value & ~(1 << bit);
}

inline uint8_t set_bit_to(const uint8_t value, const int bit, bool bit_on) {
    if (bit_on) {
        return set_bit(value, bit);
    } else {
        return clear_bit(value, bit);
    }
}
