#ifndef EMULATOR_CLOCK_H
#define EMULATOR_CLOCK_H

#include <cstdint>

class Clock {
public:
    Clock();

    void add_time(const uint8_t timestep);
};

#endif
