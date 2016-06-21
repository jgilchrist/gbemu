#pragma once

#include <cstdint>

using uint = unsigned int;

using u8  = uint8_t;
using u16 = uint16_t;
using s8  = int8_t;

const int GAMEBOY_WIDTH = 160;
const int GAMEBOY_HEIGHT = 144;

enum class Color {
    Color0, /* White */
    Color1, /* Light gray */
    Color2, /* Dark gray */
    Color3, /* Black */
};

struct Noncopyable {
    Noncopyable &operator=(const Noncopyable &) = delete;
    Noncopyable(const Noncopyable &) = delete;
    Noncopyable() = default;
};
