#pragma once

#include "cpu/cpu.h"
#include "video/screen.h"
#include "video/video.h"
#include "debugger.h"

class Gameboy {
public:
    Gameboy(Screen& inScreen, Cartridge& cartridge, bool should_debug = false);

    void run();

private:
    Screen& screen;
    MMU mmu;
    CPU cpu;
    Video video;

    Debugger debugger;

    friend class Debugger;
};
