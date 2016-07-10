#pragma once

#include <cstdint>
#include <cstdlib>

using uint = unsigned int;

using u8 = uint8_t;
using u16 = uint16_t;
using s8 = int8_t;

const int GAMEBOY_WIDTH = 160;
const int GAMEBOY_HEIGHT = 144;

const int CLOCK_RATE = 4194304;

#define fatal_error() log_error("Fatal error: %s:%d", __FILE__, __LINE__); exit(1);

enum class Color {
    Color0, /* White */
    Color1, /* Light gray */
    Color2, /* Dark gray */
    Color3, /* Black */
};

struct Noncopyable {
    Noncopyable& operator=(const Noncopyable&) = delete;
    Noncopyable(const Noncopyable&) = delete;
    Noncopyable() = default;
};
