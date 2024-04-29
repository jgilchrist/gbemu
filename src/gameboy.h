#pragma once

#include "debugger.h"
#include "input.h"
#include "cpu/cpu.h"
#include "video/video.h"
#include "serial.h"
#include "timer.h"
#include "options.h"
#include "util/log.h"

#include <memory>
#include <functional>
#include <optional>

using should_close_callback_t = std::function<bool()>;
using get_serial_data_callback_t = std::function<u8()>;

class Gameboy {
public:
    Gameboy(const std::vector<u8>& cartridge_data, Options& options,
            const std::vector<u8>& save_data = {});

    void run(
        const should_close_callback_t& _should_close_callback,
        const vblank_callback_t& _vblank_callback,
        const get_serial_data_callback_t& _get_serial_data_callback
    );

    void button_pressed(GbButton button);
    void button_released(GbButton button);

    void debug_toggle_background();
    void debug_toggle_sprites();
    void debug_toggle_window();

    auto get_cartridge_ram() const -> const std::vector<u8>&;

private:
    void tick();

    std::shared_ptr<Cartridge> cartridge;

    CPU cpu;
    friend class CPU;

    Video video;
    friend class Video;

    MMU mmu;
    friend class MMU;

    Input input;
    Serial serial;
    Timer timer;

    Debugger debugger;
    friend class Debugger;

    uint elapsed_cycles = 0;

    should_close_callback_t should_close_callback;
    get_serial_data_callback_t get_serial_data_callback;
};
