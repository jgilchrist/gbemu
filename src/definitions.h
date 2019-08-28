#pragma once

#include <cstdint>
#include <cstdlib>

using uint = unsigned int;

using u8 = uint8_t;
using u16 = uint16_t;
using s8 = int8_t;
using s16 = uint16_t;

struct Noncopyable {
    Noncopyable& operator=(const Noncopyable&) = delete;
    Noncopyable(const Noncopyable&) = delete;
    Noncopyable() = default;
    ~Noncopyable() = default;
};

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunused-parameter"
template <typename... T> void unused(T&&... unused_vars) {}
#pragma clang diagnostic pop

#define fatal_error(...) \
    log_error("Fatal error @ %s (line %d)", __PRETTY_FUNCTION__, __LINE__); \
    log_error(__VA_ARGS__); \
    exit(1);


const uint GAMEBOY_WIDTH = 160;
const uint GAMEBOY_HEIGHT = 144;
const uint BG_MAP_SIZE = 256;

const int CLOCK_RATE = 8400000;

enum class Model {
    Dmg,
    Cgb,
};

class Cycles {
public:
    Cycles(uint nCycles) : cycles(nCycles) {}

    const uint cycles;
};
