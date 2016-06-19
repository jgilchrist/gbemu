#pragma once

#include <cstdint>

using u8  = uint8_t;
using u16 = uint16_t;
using s8  = int8_t;

struct Noncopyable {
    Noncopyable &operator=(const Noncopyable &) = delete;
    Noncopyable(const Noncopyable &) = delete;
    Noncopyable() = default;
};
