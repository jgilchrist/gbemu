#include "gameboy.h"
#include "util/log.h"

Gameboy::Gameboy(Screen& inScreen, Cartridge cartridge) :
    screen(inScreen),
    mmu(cartridge),
    cpu(mmu),
    video(mmu)
{
    log_info("Initialising Gameboy");
}

void Gameboy::run() {
    while (screen.is_open()) {
        cpu.tick();
        screen.draw(video.get_framebuffer());
    }
}
