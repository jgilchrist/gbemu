#pragma once

#include "framebuffer.h"
#include "screen.h"
#include "video_mode.h"

#include "../cycles.h"
#include "../mmu.h"
#include "../register.h"

class Video {
public:
    Video(Screen& screen, MMU& mmu);

    void tick(Cycles cycles);

private:
    Screen& screen;
    MMU& mmu;
    FrameBuffer frame_buffer;

    VideoModeManager video_mode;

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
