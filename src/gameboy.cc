#include "gameboy.h"
#include "util/log.h"

Gameboy::Gameboy(std::shared_ptr<Screen> inScreen, std::shared_ptr<Input> inInput, Cartridge& cartridge, Options& options) :
    input(inInput),
    screen(inScreen),
    cpu(mmu, options),
    video(screen, cpu, mmu),
    serial(options.print_serial),
    mmu(cartridge, cpu, video, input, serial),
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
