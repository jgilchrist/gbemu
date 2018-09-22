#pragma once

#include "debugger.h"
#include "input.h"
#include "cpu/cpu.h"
#include "video/video.h"
#include "serial.h"
#include "timer.h"
#include "util/cli.h"

#include <memory>

typedef std::function<bool(void)> should_close_callback_t;

class Gameboy {
public:
    Gameboy(Cartridge& cartridge, Options& options);

    void run(
        const should_close_callback_t& _should_close_callback,
        const vblank_callback_t& _vblank_callback
    );

    void button_pressed(GbButton button);
    void button_released(GbButton button);

private:
    void tick();
    void register_vblank_callback(const vblank_callback_t& _vblank_callback);
    void register_should_close_callback(const should_close_callback_t& _should_close_callback);

    Input input;
    CPU cpu;
    Video video;
    Serial serial;
    MMU mmu;
    Timer timer;

    Debugger debugger;

    friend class Debugger;

    uint elapsed_cycles = 0;

    should_close_callback_t should_close_callback;
};
