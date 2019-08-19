#include "gameboy.h"

Gameboy::Gameboy(const std::vector<u8>& cartridge_data, Options& options,
                 const std::vector<u8>& save_data)
    : cartridge(get_cartridge(cartridge_data, save_data)),
      model(cartridge->is_cgb() ? Model::Cgb : Model::Dmg),
      cpu(mmu, options),
      video(cpu, mmu, options),
      serial(options),
      mmu(cartridge, cpu, video, input, serial, timer, options),
      debugger(*this, options) {
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

auto Gameboy::get_cartridge_ram() const -> const std::vector<u8>& {
    return cartridge->get_cartridge_ram();
}
