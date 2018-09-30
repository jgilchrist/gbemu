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
    Gameboy(std::vector<u8> cartridge_data, Options& options);

    void run(
        const should_close_callback_t& _should_close_callback,
        const vblank_callback_t& _vblank_callback
    );

    void button_pressed(GbButton button);
    void button_released(GbButton button);

    void debug_toggle_background();
    void debug_toggle_sprites();
    void debug_toggle_window();

private:
    void tick();
    void register_vblank_callback(const vblank_callback_t& _vblank_callback);
    void register_should_close_callback(const should_close_callback_t& _should_close_callback);

    std::unique_ptr<Cartridge> cartridge;
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
