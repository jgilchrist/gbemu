#pragma once

#include "color.h"

#include "../address.h"
#include "../definitions.h"
#include "../mmu.h"

#include <array>

const uint TILES_PER_LINE = 32;
const uint TILE_HEIGHT_PX = 8;
const uint TILE_WIDTH_PX = 8;

const Address TILE_SET_ZERO_ADDRESS = 0x8000;
const Address TILE_SET_ONE_ADDRESS = 0x8800;

const Address TILE_MAP_ZERO_ADDRESS = 0x9800;
const Address TILE_MAP_ONE_ADDRESS = 0x9C00;

/* A single tile contains 8 lines, each of which is two bytes */
const uint TILE_BYTES = 2 * 8;

const uint SPRITE_BYTES = 4;

class DmgTile {
public:
    DmgTile(Address& address, MMU& mmu, uint size_multiplier = 1);

    auto get_pixel(uint x, uint y) const -> GBColor;

private:
    static auto pixel_index(uint x, uint y) -> uint;
    static auto get_pixel_line(u8 byte1, u8 byte2) -> std::vector<u8>;

    DmgLogicalColor buffer[TILE_HEIGHT_PX * 2 * TILE_WIDTH_PX];
};
