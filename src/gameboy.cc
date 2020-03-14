#include "gameboy.h"

Gameboy::Gameboy(Model _model, std::vector<u8> cartridge_data, Options& options, std::vector<u8> save_data) :
    model(_model),
    cartridge(get_cartridge(std::move(cartridge_data), std::move(save_data))),
    cpu(model, mmu, options),
    video(model, cpu, mmu, options),
    serial(options),
    mmu(model, cartridge, cpu, video, input, serial, timer, options),
    debugger(*this, options)
{
    if (options.disable_logs) log_set_level(LogLevel::Error);

    log_set_level(options.trace
        ? LogLevel::Trace
        : LogLevel::Info
    );
}

void Gameboy::button_pressed(GbButton button) {
    input.button_pressed(button);
}

void Gameboy::button_released(GbButton button) {
    input.button_released(button);
}

void Gameboy::set_model(Model newModel) {
    model = newModel;

    log_info("Switched mode to %s",
        model == Model::Dmg ? "DMG" : "CGB"
    );
}

void Gameboy::debug_toggle_background() {
    video.debug_disable_background = !video.debug_disable_background;
}

void Gameboy::debug_toggle_sprites() {
    video.debug_disable_sprites = !video.debug_disable_sprites;
}

void Gameboy::debug_toggle_window() {
    video.debug_disable_window = !video.debug_disable_window;
}

void Gameboy::run(
    const should_close_callback_t& _should_close_callback,
    const dmg_vblank_callback_t& _dmg_vblank_callback,
    const cgb_vblank_callback_t& _cgb_vblank_callback
) {
    should_close_callback = _should_close_callback;

    video.register_vblank_callbacks(
        _dmg_vblank_callback,
        _cgb_vblank_callback
    );

    while (!should_close_callback()) {
        tick();
    }

    debugger.set_enabled(false);
}

void Gameboy::tick() {
    debugger.cycle();

    auto cycles = cpu.tick();
    elapsed_cycles += cycles.cycles;

    video.tick(cycles);
    timer.tick(cycles.cycles);
}

const std::vector<u8>& Gameboy::get_cartridge_ram() const {
    return cartridge->get_cartridge_ram();
}
