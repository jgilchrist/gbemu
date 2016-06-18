#pragma once

#include "cpu/cpu.h"

class Gameboy {
public:
    Gameboy(Cartridge cartridge);

    void run();

private:
    MMU mmu;
    CPU cpu;
};
