#ifndef EMULATOR_GAMEBOY_H
#define EMULATOR_GAMEBOY_H

#include "cpu.h"

class Gameboy {
public:
    Gameboy();

private:
    CPU cpu;
};

#endif
