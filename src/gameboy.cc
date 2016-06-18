#include "gameboy.h"
#include "util/log.h"

Gameboy::Gameboy(Cartridge cartridge) :
    mmu(cartridge),
    cpu(mmu)
{
    log_info("Initialising Gameboy");
}

void Gameboy::run() {
    while (true) {
        cpu.tick();
    }
}
