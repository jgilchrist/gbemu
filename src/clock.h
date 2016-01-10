#pragma once

#include <cstdint>

class Clock {
public:
    Clock();

    void add_time(const uint8_t timestep);
};
