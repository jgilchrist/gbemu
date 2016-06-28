#include "gameboy.h"
#include "util/log.h"

Gameboy::Gameboy(Screen& inScreen, Cartridge cartridge) :
    screen(inScreen),
    mmu(cartridge, video),
    cpu(mmu),
    video(screen, mmu)
{
    log_info("Initialising Gameboy");
}

void Gameboy::run() {
    unsigned elapsed_cycles = 0;

    while (screen.is_open()) {
        auto cycles = cpu.tick();
        elapsed_cycles += cycles.cycles;

        log_trace("Cycles: %d", elapsed_cycles);

        video.tick(cycles);
    }
}
