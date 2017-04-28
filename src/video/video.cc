#include "video.h"

#include "../cpu/cpu.h"

#include "../util/bitwise.h"
#include "../util/log.h"

using bitwise::check_bit;

Video::Video(std::shared_ptr<Screen> inScreen, CPU& inCPU, MMU& inMMU) :
    screen(inScreen),
    cpu(inCPU),
    mmu(inMMU),
    buffer(FRAMEBUFFER_SIZE, FRAMEBUFFER_SIZE)
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
                /* write_scanline(line.value()); */
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
                    write_scanline(0);
                    draw();
                    line.reset();
                    current_mode = VideoMode::ACCESS_OAM;
                };
            }
            break;
    }
}

bool Video::display_enabled() const { return check_bit(control_byte, 7); }
bool Video::window_tile_map() const { return check_bit(control_byte, 6); }
bool Video::window_enabled() const { return check_bit(control_byte, 5); }
bool Video::bg_window_tile_data() const { return check_bit(control_byte, 4); }
bool Video::bg_tile_map_display() const { return check_bit(control_byte, 3); }
bool Video::sprite_size() const { return check_bit(control_byte, 2); }
bool Video::sprites_enabled() const { return check_bit(control_byte, 1); }
bool Video::bg_enabled() const { return check_bit(control_byte, 0); }

void Video::write_scanline(u8 current_line) {
    if (!display_enabled()) { return; }

    if (bg_enabled()) {
        for (uint tile_y = 0; tile_y < TILES_PER_LINE; tile_y++) {
            for (uint tile_x = 0; tile_x < TILES_PER_LINE; tile_x++) {
                draw_tile(tile_x, tile_y);
            }
        }
    }
}

void Video::draw_tile(const uint tile_x, const uint tile_y) {
    /* Note: tileset two uses signed numbering to share half the tiles with tileset 1 */
    bool tile_set_zero = bg_window_tile_data();
    bool tile_map_zero = !bg_tile_map_display();

    Address tile_set_location = tile_set_zero
        ? TILE_SET_ZERO_LOCATION
        : TILE_SET_ONE_LOCATION;

    Address tile_map_location = tile_map_zero
        ? TILE_MAP_ZERO_LOCATION
        : TILE_MAP_ONE_LOCATION;

    /* Work out the index of the tile in the array of all tiles */
    uint tile_index = tile_y * TILES_PER_LINE + tile_x;

    /* Work out the address of the tile ID from the tile map */
    Address tile_id_address = tile_map_location + tile_index;

    /* Grab the tile number from the tile map */
    u8 tile_id = mmu.read(tile_id_address);

    uint tile_offset = tile_id * TILE_BYTES;
    Address tile_address = tile_set_location + tile_offset;

    Tile tile(tile_address, mmu);

    uint y_in_framebuffer = TILE_HEIGHT_PX * tile_y;
    uint x_in_framebuffer = TILE_WIDTH_PX * tile_x;

    for (uint y = 0; y < TILE_HEIGHT_PX; y++) {
        for (uint x = 0; x < TILE_WIDTH_PX; x++) {
            GBColor color = tile.get_pixel(x, y);
            buffer.set_pixel(x_in_framebuffer + x, y_in_framebuffer + y, color);
        }
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
    screen->draw(buffer, scroll_x.value(), scroll_y.value(), get_bg_palette());
}
