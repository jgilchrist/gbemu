#pragma once

#include "../register.h"
#include "../mmu.h"

const int GAMEBOY_WIDTH = 160;
const int GAMEBOY_HEIGHT = 144;

enum class Color {
    Color1,
    Color2,
    Color3,
    Color4
};

class Video {
public:
    Video(MMU& mmu);

private:
    MMU& mmu;

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
