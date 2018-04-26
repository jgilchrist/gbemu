#include "gameboy.h"
#include "util/log.h"

Gameboy::Gameboy(std::shared_ptr<Screen> inScreen, Cartridge& cartridge, Options& options) :
    screen(inScreen),
    cpu(mmu, options),
    video(screen, cpu, mmu),
    serial(),
    mmu(cartridge, cpu, video, serial),
    debugger(*this, options.debugger)
{
    log_info("Initialising Gameboy");
    log_info("");
}

void Gameboy::run() {
    uint elapsed_cycles = 0;

    while (screen->is_open()) {
        debugger.cycle();

        auto cycles = cpu.tick();
        elapsed_cycles += cycles.cycles;

        video.tick(cycles);
    }
}
