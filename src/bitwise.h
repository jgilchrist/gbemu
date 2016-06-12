#pragma once

#include <cstdint>

inline uint16_t compose_bytes(const uint8_t low, const uint8_t high) {
    return (high << 8) + low;
}

inline bool check_bit(const uint8_t value, int bit) {
    return (value & (1 << bit)) != 0;
}

inline uint8_t set_bit(const uint8_t value, int bit) {
    return static_cast<uint8_t>(value | (1 << bit));
}
