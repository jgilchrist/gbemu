#include "tile.h"

#include "color.h"
#include "../util/bitwise.h"

using bitwise::bit_value;

Tile::Tile(Address& tile_address, MMU& mmu, uint size_multiplier) {
    /* Set the whole framebuffer to be black */
    for (uint x = 0; x < TILE_WIDTH_PX; x++) {
        for (uint y = 0; y < TILE_HEIGHT_PX * size_multiplier; y++) {
            buffer[pixel_index(x, y)] = PaletteIndex::Color0;
        }
    }

    for (uint tile_line = 0; tile_line < TILE_HEIGHT_PX * size_multiplier; tile_line++) {
        /* 2 (bytes per line of pixels) * y (lines) */
        uint index_into_tile = 2 * tile_line;
        Address line_start = tile_address + index_into_tile;

        u8 pixels_1 = mmu.read(line_start);
        u8 pixels_2 = mmu.read(line_start + 1);

        std::vector<u8> pixel_line = get_pixel_line(pixels_1, pixels_2);

        for (uint x = 0; x < TILE_WIDTH_PX; x++) {
            buffer[pixel_index(x, tile_line)] = get_color(pixel_line[x]);
        }
    }
}

PaletteIndex Tile::get_pixel(uint x, uint y) const {
    return buffer[pixel_index(x, y)];
}

std::vector<u8> Tile::get_pixel_line(u8 byte1, u8 byte2) const {
    using bitwise::bit_value;

    std::vector<u8> pixel_line;
    for (u8 i = 0; i < 8; i++) {
        u8 color_value = static_cast<u8>((bit_value(byte2, 7-i) << 1) | bit_value(byte1, 7-i));
        pixel_line.push_back(color_value);
    }

    return pixel_line;
}

inline uint Tile::pixel_index(uint x, uint y) {
    return (y * TILE_HEIGHT_PX) + x;
}
