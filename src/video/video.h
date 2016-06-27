#pragma once

#include "framebuffer.h"
#include "screen.h"

#include "../cycles.h"
#include "../mmu.h"
#include "../register.h"


enum class VideoMode {
    ACCESS_OAM,
    ACCESS_VRAM,
    HBLANK,
    VBLANK,
};

class Video {
public:
    Video(Screen& screen, MMU& mmu);

    void tick(Cycles cycles);

private:
    void write_scanline(u8 line);
    void draw();

    Screen& screen;
    MMU& mmu;
    FrameBuffer frame_buffer;

    VideoMode current_mode;
    unsigned cycle_counter;
    u8 line;

    /* TODO: Annotate each register with its register name */

    ByteRegister lcd_control;
    ByteRegister lcd_status;

    ByteRegister scroll_y;
    ByteRegister scroll_x;

    /* LCDC Y-coordinate */
    ByteRegister ly;
    ByteRegister ly_compare;

    ByteRegister window_y;
    ByteRegister window_x; /* Note: x - 7 */

    ByteRegister bg_palette;
    ByteRegister sprite0_palette; /* OBP0 */
    ByteRegister sprite1_palette; /* OBP1 */

    /* TODO: LCD Color Palettes (CGB) */
    /* TODO: LCD VRAM Bank (CGB) */

    ByteRegister dma_transfer; /* DMA */

    /* TODO: LCD VRAM DMA Transfers */
};

const int CLOCKS_PER_HBLANK = 204; /* Mode 0 */
const int CLOCKS_PER_SCANLINE_OAM = 80; /* Mode 2 */
const int CLOCKS_PER_SCANLINE_VRAM = 172; /* Mode 3 */
const int CLOCKS_PER_SCANLINE = (CLOCKS_PER_SCANLINE_OAM + CLOCKS_PER_SCANLINE_VRAM + CLOCKS_PER_HBLANK);

const int CLOCKS_PER_VBLANK = 4560; /* Mode 1 */
const int SCANLINES_PER_FRAME = 144;
const int CLOCKS_PER_FRAME = (CLOCKS_PER_SCANLINE * SCANLINES_PER_FRAME) + CLOCKS_PER_VBLANK;
