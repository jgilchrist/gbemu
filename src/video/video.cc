#include "video.h"

#include "../util/bitwise.h"
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
                write_scanline(line.value());
                line.increment();

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
                line.increment();

                cycle_counter = cycle_counter % CLOCKS_PER_SCANLINE;

                /* Line 155 (index 154) is the last line */
                if (line == 154) {
                    draw();
                    line.reset();
                    current_mode = VideoMode::ACCESS_OAM;
                };
            }
            break;
    }
}

void Video::write_scanline(u8 current_line) {
    /* TODO: Support tilemap switching */
    /* TODO: Support tileset switching */
    /* Note: tileset two uses signed numbering to share half the tiles with tileset 1 */
    bool tile_set_zero = true;
    bool tile_map_zero = true;

    Address tile_set_location = tile_set_zero
        ? TILE_SET_ZERO_LOCATION
        : TILE_SET_ONE_LOCATION;

    Address tile_map_location = tile_map_zero
        ? TILE_MAP_ZERO_LOCATION
        : TILE_MAP_ONE_LOCATION;

    /* Step 1:
     * Using scroll x, scroll y and the current line to determine the start tile
     * and work out the tile index */

    /* Work out the x,y coordinates of the top left pixel of the 160x144 screen in
     * the 256x256 background map */
    const uint y_pixel_start = current_line + scroll_y.value();
    const uint x_pixel_start = scroll_x.value();

    /* Work out which tile contains the top left pixel of the screen. This is the
     * 'start tile' */
    const uint tile_y = y_pixel_start / TILE_HEIGHT_PX;
    const uint tile_x = x_pixel_start / TILE_WIDTH_PX;

    /* Work out the index of the tile in the array of all tiles */
    uint tile_address_index = tile_y * TILES_PER_LINE + tile_x;


    /* Step 2:
     * Using scroll y and scroll x, determine which line of pixels to use in the tiles
     * This is achieved by masking with 0111 */

    const u8 TILE_MASK = 7;

    const u8 y = y_pixel_start & TILE_MASK;
    u8 x = x_pixel_start & TILE_MASK;


    /* Step 3:
     * Grab the tile number from the tile map */

    Address tile_id_address = tile_map_location + tile_address_index;

    u8 tile_id = mmu.read(tile_id_address);


    /* Step 4:
     * Grab the tile specified by the tile number from the tile set */

    TileInfo current_tile = get_tile_info(tile_set_location, tile_id, y);


    /* Step 5:
     * Loop down the tiles to draw each pixel in the line */
    /* TODO: Stop working pixel-by-pixel, work tile-by-tile instead */

    for (uint screen_x = 0; screen_x < GAMEBOY_WIDTH; screen_x++) {
        u8 pixel_value = current_tile.pixels[x];

        /* TODO: If the palette is switched, do all pixels retroactively switch? */
        GBColor pixel_color = get_color(pixel_value);
        frame_buffer.set_pixel(screen_x, current_line, pixel_color);
        x++;

        /* When x is 8, we have crossed over into another tile, so the tile
         * indexes should be updated; */
        if (x == 8) {
            x = 0;

            /* We move to the next tile in the line */
            tile_address_index = tile_address_index + 1;
            tile_id_address = tile_map_location + tile_address_index;

            /* Read the new tile ID */
            tile_id = mmu.read(tile_id_address);

            current_tile = get_tile_info(tile_set_location, tile_id, y);
        }
    }
}

TileInfo Video::get_tile_info(Address tile_set_location, u8 tile_id, u8 tile_line) const {
    uint tile_offset = tile_id * TILE_BYTES;
    Address tile_address = tile_set_location + tile_offset;

    /* 2 (bytes per line of pixels) * y (lines) */
    uint index_into_tile = 2 * tile_line;
    Address line_start = tile_address + index_into_tile;

    u8 pixels_1 = mmu.read(line_start);
    u8 pixels_2 = mmu.read(line_start + 1);

    std::vector<u8> pixel_line = get_pixel_line(pixels_1, pixels_2);

    return TileInfo {
        tile_line,
        pixel_line
    };
}

std::vector<u8> Video::get_pixel_line(u8 byte1, u8 byte2) const {
    using bitwise::bit_value;

    std::vector<u8> pixel_line;
    for (u8 i = 0; i < 8; i++) {
        u8 color_value = static_cast<u8>((bit_value(byte2, 7-i) << 1) | bit_value(byte1, 7-i));
        pixel_line.push_back(color_value);
    }

    return pixel_line;
}

GBColor Video::get_color(u8 pixel_value) const {
    switch (pixel_value) {
        case 0:
            return GBColor::Color0;
        case 1:
            return GBColor::Color1;
        case 2:
            return GBColor::Color2;
        case 3:
            return GBColor::Color3;
        default:
            fatal_error("Invalid color value: %d", pixel_value);
    }
}

BGPalette Video::get_bg_palette() const {
    using bitwise::compose_bits;
    using bitwise::bit_value;

    /* TODO: Reduce duplication */
    u8 color0 = compose_bits(bit_value(bg_palette.value(), 1), bit_value(bg_palette.value(), 0));
    u8 color1 = compose_bits(bit_value(bg_palette.value(), 3), bit_value(bg_palette.value(), 2));
    u8 color2 = compose_bits(bit_value(bg_palette.value(), 5), bit_value(bg_palette.value(), 4));
    u8 color3 = compose_bits(bit_value(bg_palette.value(), 7), bit_value(bg_palette.value(), 6));

    Color real_color_0 = get_real_color(color0);
    Color real_color_1 = get_real_color(color1);
    Color real_color_2 = get_real_color(color2);
    Color real_color_3 = get_real_color(color3);

    return { real_color_0, real_color_1, real_color_2, real_color_3 };
}

Color Video::get_real_color(u8 pixel_value) const {
    switch (pixel_value) {
        case 0: return Color::White;
        case 1: return Color::LightGray;
        case 2: return Color::DarkGray;
        case 3: return Color::Black;
        default:
            fatal_error("Invalid color value");
    }
}

void Video::draw() {
    screen.draw(frame_buffer, get_bg_palette());
}
