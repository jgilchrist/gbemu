#pragma once

#include "framebuffer.h"
#include "screen.h"
#include "tile.h"

#include "../cycles.h"
#include "../mmu.h"
#include "../register.h"

#include <vector>

enum class VideoMode {
    ACCESS_OAM,
    ACCESS_VRAM,
    HBLANK,
    VBLANK,
};

struct TileInfo {
    u8 line;
    std::vector<u8> pixels;
};

class Video {
public:
    Video(Screen& inScreen, MMU& inMMU);

    void tick(Cycles cycles);

    /* TODO: Annotate each register with its register name */

    ByteRegister lcd_control;
    ByteRegister lcd_status;

    ByteRegister scroll_y;
    ByteRegister scroll_x;

    /* LCDC Y-coordinate */
    ByteRegister line; /* Line y-position: register LY */
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

private:
    void write_scanline(u8 current_line);
    void draw();
    void draw_tile(FrameBuffer& buffer, const uint tile_x, const uint tile_y);

    TileInfo get_tile_info(Address tile_set_location, u8 tile_id, u8 tile_line) const;

    Color get_real_color(u8 pixel_value) const;
    BGPalette get_bg_palette() const;

    Screen& screen;
    MMU& mmu;
    FrameBuffer screen_buffer;

    VideoMode current_mode;
    unsigned cycle_counter;
};

const uint CLOCKS_PER_HBLANK = 204; /* Mode 0 */
const uint CLOCKS_PER_SCANLINE_OAM = 80; /* Mode 2 */
const uint CLOCKS_PER_SCANLINE_VRAM = 172; /* Mode 3 */
const uint CLOCKS_PER_SCANLINE =
    (CLOCKS_PER_SCANLINE_OAM + CLOCKS_PER_SCANLINE_VRAM + CLOCKS_PER_HBLANK);

const uint CLOCKS_PER_VBLANK = 4560; /* Mode 1 */
const uint SCANLINES_PER_FRAME = 144;
const uint CLOCKS_PER_FRAME = (CLOCKS_PER_SCANLINE * SCANLINES_PER_FRAME) + CLOCKS_PER_VBLANK;

const uint FRAMEBUFFER_SIZE = 255;
