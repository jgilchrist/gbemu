#include "video.h"

#include "../util/log.h"

Video::Video(Screen& inScreen, MMU& inMMU) :
    screen(inScreen),
    mmu(inMMU)
{
}

void Video::tick(Cycles cycles) {
    cycle_counter += cycles.cycles;

    switch (current_mode) {
        case VideoMode::ACCESS_OAM:
            if (cycle_counter >= CLOCKS_PER_SCANLINE_OAM) {
                cycle_counter = cycle_counter % CLOCKS_PER_SCANLINE_OAM;
                current_mode = VideoMode::ACCESS_VRAM;
            }
            break;
        case VideoMode::ACCESS_VRAM:
            if (cycle_counter >= CLOCKS_PER_SCANLINE_VRAM) {
                cycle_counter = cycle_counter % CLOCKS_PER_SCANLINE_VRAM;
                current_mode = VideoMode::HBLANK;
            }
            break;
        case VideoMode::HBLANK:
            if (cycle_counter >= CLOCKS_PER_HBLANK) {
                write_scanline(line);
                line++;

                cycle_counter = cycle_counter % CLOCKS_PER_HBLANK;

                /* Line 145 (index 144) is the first line of VBLANK */
                if (line == 144) {
                    current_mode = VideoMode::VBLANK;
                } else {
                    current_mode = VideoMode::ACCESS_OAM;
                }
            }
            break;
        case VideoMode::VBLANK:
            if (cycle_counter >= CLOCKS_PER_SCANLINE) {
                line++;

                cycle_counter = cycle_counter % CLOCKS_PER_SCANLINE;

                /* Line 155 (index 154) is the last line */
                if (line == 154) {
                    draw();
                    line = 0;
                    current_mode = VideoMode::ACCESS_OAM;
                };
            }
            break;
    }
}

void Video::write_scanline(u8 drawn_line) {
    /* TODO */
}

void Video::draw() {
    log_debug("Drawing to screen");
    screen.draw(frame_buffer);
}
