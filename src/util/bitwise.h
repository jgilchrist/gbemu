#pragma once

#include "../definitions.h"
#include "log.h"

namespace bitwise {

inline u16 compose_bytes(const u8 high, const u8 low) {
    return static_cast<u16>((high << 8) + low);
}

inline bool check_bit(const u8 value, const u8 bit) {
    return (value & (1 << bit)) != 0;
}

inline u8 set_bit(const u8 value, const u8 bit) {
    auto value_set = value | (1 << bit);
    return static_cast<u8>(value_set);
}

inline u8 clear_bit(const u8 value, const u8 bit) {
    auto value_cleared = value & ~(1 << bit);
    return static_cast<u8>(value_cleared);
}

inline u8 set_bit_to(const u8 value, const u8 bit, bool bit_on) {
    if (bit_on) {
        return set_bit(value, bit);
    } else {
        return clear_bit(value, bit);
    }
}

} // namespace bitwise
