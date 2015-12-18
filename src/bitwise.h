#ifndef EMULATOR_BITWISE_H
#define EMULATOR_BITWISE_H

#include <cstdint>

inline uint16_t compose_bytes(const uint8_t low, const uint8_t high) {
    return (high << 8) + low;
};

#endif
