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
                lcd_status.set_bit_to(1, 1);
                lcd_status.set_bit_to(0, 1);
                current_mode = VideoMode::ACCESS_VRAM;
            }
            break;
        case VideoMode::ACCESS_VRAM:
            if (cycle_counter >= CLOCKS_PER_SCANLINE_VRAM) {
                cycle_counter = cycle_counter % CLOCKS_PER_SCANLINE_VRAM;
                current_mode = VideoMode::HBLANK;

                bool hblank_interrupt = bitwise::check_bit(lcd_status.value(), 3);

                if (hblank_interrupt) {
                    cpu.interrupt_flag.set_bit_to(1, true);
                }

                bool ly_coincidence_interrupt = bitwise::check_bit(lcd_status.value(), 6);
                bool ly_coincidence = ly_compare.value() == line.value();
                if (ly_coincidence_interrupt && ly_coincidence) {
                    cpu.interrupt_flag.set_bit_to(1, true);
                }
                lcd_status.set_bit_to(2, ly_coincidence);

                lcd_status.set_bit_to(1, 0);
                lcd_status.set_bit_to(0, 0);
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
                    lcd_status.set_bit_to(1, 0);
                    lcd_status.set_bit_to(0, 1);
                    cpu.interrupt_flag.set_bit_to(0, true);
                } else {
                    lcd_status.set_bit_to(1, 1);
                    lcd_status.set_bit_to(0, 0);
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
                    /* We don't currently draw line-by-line so we pass 0 */
                    write_scanline(0);
                    draw();
                    buffer.reset();
                    line.reset();
                    current_mode = VideoMode::ACCESS_OAM;
                    lcd_status.set_bit_to(1, 1);
                    lcd_status.set_bit_to(0, 0);
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

    for (uint sprite_n = 0; sprite_n < 40; sprite_n++) {
        draw_sprite(sprite_n);
    }
}

void Video::draw_tile(const uint tile_x, const uint tile_y) {
    /* Note: tileset two uses signed numbering to share half the tiles with tileset 1 */
    bool tile_set_zero = bg_window_tile_data();
    bool tile_map_zero = !bg_tile_map_display();

    Palette palette = load_palette(bg_palette);

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

    uint tile_offset = tile_set_zero
        ? tile_id * TILE_BYTES
        : (static_cast<s8>(tile_id) + 128) * TILE_BYTES;

    Address tile_address = tile_set_location + tile_offset;

    Tile tile(tile_address, mmu);

    uint y_start_in_framebuffer = TILE_HEIGHT_PX * tile_y;
    uint x_start_in_framebuffer = TILE_WIDTH_PX * tile_x;

    for (uint y = 0; y < TILE_HEIGHT_PX; y++) {
        for (uint x = 0; x < TILE_WIDTH_PX; x++) {
            GBColor gb_color = tile.get_pixel(x, y);
            Color screen_color = get_color_from_palette(gb_color, palette);

            uint actual_x = x_start_in_framebuffer + x;
            uint actual_y = y_start_in_framebuffer + y;

            buffer.set_pixel(actual_x, actual_y, screen_color);
        }
    }
}

void Video::draw_sprite(const uint sprite_n) {
    using bitwise::check_bit;

    uint sprite_size_multiplier = sprite_size()
        ? 2 : 1;

    /* Sprites are always taken from the first tileset */
    Address tile_set_location = TILE_SET_ZERO_LOCATION;

    /* Each sprite is represented by 4 bytes, or 8 bytes in 8x16 mode */
    Address offset_in_oam = sprite_n * SPRITE_BYTES;

    Address oam_start = 0xFE00 + offset_in_oam.value();
    u8 sprite_y = mmu.read(oam_start);
    u8 sprite_x = mmu.read(oam_start + 1);
    u8 pattern_n = mmu.read(oam_start + 2);
    u8 sprite_attrs = mmu.read(oam_start + 3);

    /* If the sprite would be drawn offscreen, don't draw it */
    if (sprite_y == 0 || sprite_y >= 160) { return; }
    if (sprite_x == 0 || sprite_x >= 168) { return; }

    /* Bits 0-3 are used only for CGB */
    bool use_palette_1 = check_bit(sprite_attrs, 4);
    bool flip_x = check_bit(sprite_attrs, 5);
    bool flip_y = check_bit(sprite_attrs, 6);
    bool obj_behind_bg = check_bit(sprite_attrs, 7);

    Palette palette = use_palette_1
        ? load_palette(sprite_palette_1)
        : load_palette(sprite_palette_0);

    uint tile_offset = pattern_n * TILE_BYTES;

    Address pattern_address = tile_set_location + tile_offset;

    Tile tile(pattern_address, mmu, sprite_size_multiplier);
    int start_y = sprite_y - 16;
    int start_x = sprite_x - 8;

    for (uint y = 0; y < TILE_HEIGHT_PX * sprite_size_multiplier; y++) {
        for (uint x = 0; x < TILE_WIDTH_PX; x++) {
            uint maybe_flipped_y = !flip_y ? y : (TILE_HEIGHT_PX * sprite_size_multiplier) - y - 1;
            uint maybe_flipped_x = !flip_x ? x : TILE_WIDTH_PX - x - 1;

            GBColor gb_color = tile.get_pixel(maybe_flipped_x, maybe_flipped_y);

            // Color 0 is transparent
            if (gb_color == GBColor::Color0) { continue; }

            Color screen_color = get_color_from_palette(gb_color, palette);

            int pixel_x = start_x + x;
            int pixel_y = start_y + y;

            if (pixel_x < 0 || pixel_x > GAMEBOY_WIDTH) { continue; }
            if (pixel_y < 0 || pixel_y > GAMEBOY_HEIGHT) { continue; }

            buffer.set_pixel(pixel_x, pixel_y, screen_color);
        }
    }
}

Palette Video::load_palette(ByteRegister& palette_register) const {
    using bitwise::compose_bits;
    using bitwise::bit_value;

    /* TODO: Reduce duplication */
    u8 color0 = compose_bits(bit_value(palette_register.value(), 1), bit_value(palette_register.value(), 0));
    u8 color1 = compose_bits(bit_value(palette_register.value(), 3), bit_value(palette_register.value(), 2));
    u8 color2 = compose_bits(bit_value(palette_register.value(), 5), bit_value(palette_register.value(), 4));
    u8 color3 = compose_bits(bit_value(palette_register.value(), 7), bit_value(palette_register.value(), 6));

    Color real_color_0 = get_real_color(color0);
    Color real_color_1 = get_real_color(color1);
    Color real_color_2 = get_real_color(color2);
    Color real_color_3 = get_real_color(color3);

    return { real_color_0, real_color_1, real_color_2, real_color_3 };
}

Color Video::get_color_from_palette(GBColor color, const Palette& palette) {
    switch (color) {
        case GBColor::Color0: return palette.color0;
        case GBColor::Color1: return palette.color1;
        case GBColor::Color2: return palette.color2;
        case GBColor::Color3: return palette.color3;
    }
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
    screen->draw(buffer, scroll_x.value(), scroll_y.value());
}
