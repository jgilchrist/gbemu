#pragma once

#include "debugger.h"
#include "input.h"
#include "cpu/cpu.h"
#include "video/screen.h"
#include "video/video.h"
#include "serial.h"
#include "util/cli.h"

#include <memory>

class Gameboy {
public:
    Gameboy(std::shared_ptr<Screen> inScreen, std::shared_ptr<Input> inInput, Cartridge& cartridge, Options& options);

    void run();

private:
    std::shared_ptr<Input> input;
    std::shared_ptr<Screen> screen;
    CPU cpu;
    Video video;
    Serial serial;
    MMU mmu;

    Debugger debugger;

    friend class Debugger;
};
