#pragma once

#include "framebuffer.h"
#include "screen.h"

#include "../register.h"
#include "../mmu.h"

const int CLOCKS_PER_HBLANK = 204; /* Mode 0 */
const int CLOCKS_PER_SCANLINE_OAM = 80; /* Mode 2 */
const int CLOCKS_PER_SCANLINE_VRAM = 172; /* Mode 3 */
const int CLOCKS_PER_SCANLINE = \
    (CLOCKS_PER_SCANLINE_OAM + CLOCKS_PER_SCANLINE_VRAM + CLOCKS_PER_HBLANK);

const int CLOCKS_PER_VBLANK = 4560; /* Mode 1 */
const int SCANLINES_PER_FRAME = 144;
const int CLOCKS_PER_FRAME = \
    (CLOCKS_PER_SCANLINE * SCANLINES_PER_FRAME) + CLOCKS_PER_VBLANK;

class Video {
public:
    Video(Screen& screen, MMU& mmu);

    const FrameBuffer& get_framebuffer();

private:
    MMU& mmu;
    Screen& screen;
    FrameBuffer frame_buffer;

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
