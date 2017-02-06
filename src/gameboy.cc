#include "gameboy.h"
#include "util/log.h"

Gameboy::Gameboy(Screen& inScreen, Cartridge& cartridge, bool should_debug) :
    screen(inScreen),
    cpu(mmu),
    video(screen, mmu),
    mmu(cartridge, cpu, video),
    debugger(*this, should_debug)
{
    log_info("Initialising Gameboy");
    log_info("");
}

void Gameboy::run() {
    uint elapsed_cycles = 0;

    while (screen.is_open()) {
        debugger.cycle();

        auto cycles = cpu.tick();
        elapsed_cycles += cycles.cycles;

        video.tick(cycles);
    }
}
