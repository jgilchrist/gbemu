#include "video.h"

#include "color.h"
#include "../cpu/cpu.h"

#include "../util/bitwise.h"
#include "../util/log.h"

using bitwise::check_bit;

Video::Video(Model& inModel, CPU& inCPU, MMU& inMMU, Options& inOptions) :
    model(inModel),
    cpu(inCPU),
    mmu(inMMU),
    dmg_buffer(GAMEBOY_WIDTH, GAMEBOY_HEIGHT),
    cgb_buffer(GAMEBOY_WIDTH, GAMEBOY_HEIGHT)
{
    video_ram = std::vector<u8>(0x4000);
}

u8 Video::read(const Address& address) {
    return video_ram.at(calculate_vram_address(address));
}

void Video::write(const Address& address, u8 value) {
    video_ram.at(calculate_vram_address(address)) = value;
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

                write_scanline(line.value());
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
                    write_sprites();
                    draw();
                    dmg_buffer.reset();
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

    if (bg_enabled() && !debug_disable_background) {
        draw_bg_line(current_line);
    }

    if (window_enabled() && !debug_disable_window) {
        draw_window_line(current_line);
    }
}

void Video::write_sprites() {
    if (!sprites_enabled() || debug_disable_sprites) { return; }

    for (uint sprite_n = 0; sprite_n < 40; sprite_n++) {
        draw_sprite(sprite_n);
    }
}

void Video::draw_bg_line(uint current_line) {
    /* Note: tileset two uses signed numbering to share half the tiles with tileset 1 */
    bool use_tile_set_zero = bg_window_tile_data();
    bool use_tile_map_zero = !bg_tile_map_display();

    DmgPalette palette = load_palette(bg_palette);

    Address tile_set_address = use_tile_set_zero
        ? TILE_SET_ZERO_ADDRESS
        : TILE_SET_ONE_ADDRESS;

    Address tile_map_address = use_tile_map_zero
        ? TILE_MAP_ZERO_ADDRESS
        : TILE_MAP_ONE_ADDRESS;

    /* The pixel row we're drawing on the screen is constant since we're only
     * drawing a single line */
    uint screen_y = current_line;

    for (uint screen_x = 0; screen_x < GAMEBOY_WIDTH; screen_x++) {
        /* Work out the position of the pixel in the framebuffer */
        uint scrolled_x = screen_x + scroll_x.value();
        uint scrolled_y = screen_y + scroll_y.value();

        /* Work out the index of the pixel in the full background map */
        uint bg_map_x = scrolled_x % BG_MAP_SIZE;
        uint by_map_y = scrolled_y % BG_MAP_SIZE;

        /* Work out which tile of the bg_map this pixel is in, and the index of that tile
         * in the array of all tiles */
        uint tile_x = bg_map_x / TILE_WIDTH_PX;
        uint tile_y = by_map_y / TILE_HEIGHT_PX;

        /* Work out which specific (x,y) inside that tile we're going to render */
        uint tile_pixel_x = bg_map_x % TILE_WIDTH_PX;
        uint tile_pixel_y = by_map_y % TILE_HEIGHT_PX;

        /* Work out the address of the tile ID from the tile map */
        uint tile_index = tile_y * TILES_PER_LINE + tile_x;
        Address tile_id_address = tile_map_address + tile_index;

        /* Grab the ID of the tile we'll get data from in the tile map */
        u8 tile_id = mmu.read(tile_id_address);

        /* Calculate the offset from the start of the tile data memory where
         * the data for our tile lives */
        uint tile_data_mem_offset = use_tile_set_zero
            ? tile_id * TILE_BYTES
            : (static_cast<s8>(tile_id) + 128) * TILE_BYTES;

        /* Calculate the extra offset to the data for the line of pixels we
         * are rendering from.
         * 2 (bytes per line of pixels) * y (lines) */
        uint tile_data_line_offset = tile_pixel_y * 2;

        Address tile_line_data_start_address = tile_set_address + tile_data_mem_offset + tile_data_line_offset;

        /* FIXME: We fetch the full line of pixels for each pixel in the tile
         * we render. This could be altered to work in a way that avoids re-fetching
         * for a more performant renderer */
        u8 pixels_1 = mmu.read(tile_line_data_start_address);
        u8 pixels_2 = mmu.read(tile_line_data_start_address + 1);

        DmgLogicalColor pixel_color = get_pixel_from_line(pixels_1, pixels_2, tile_pixel_x);
        DmgColor screen_color = get_color_from_palette(pixel_color, palette);

        dmg_buffer.set_pixel(screen_x, screen_y, screen_color);
    }
}

void Video::draw_window_line(uint current_line) {
    /* Note: tileset two uses signed numbering to share half the tiles with tileset 1 */
    bool use_tile_set_zero = bg_window_tile_data();
    bool use_tile_map_zero = !window_tile_map();

    DmgPalette palette = load_palette(bg_palette);

    Address tile_set_address = use_tile_set_zero
        ? TILE_SET_ZERO_ADDRESS
        : TILE_SET_ONE_ADDRESS;

    Address tile_map_address = use_tile_map_zero
        ? TILE_MAP_ZERO_ADDRESS
        : TILE_MAP_ONE_ADDRESS;

    uint screen_y = current_line;
    uint scrolled_y = screen_y - window_y.value();

    if (scrolled_y >= GAMEBOY_HEIGHT) { return; }
    // if (!is_on_screen_y(scrolled_y)) { return; }

    for (uint screen_x = 0; screen_x < GAMEBOY_WIDTH; screen_x++) {
        /* Work out the position of the pixel in the framebuffer */
        uint scrolled_x = screen_x + window_x.value() - 7;

        /* Work out which tile of the bg_map this pixel is in, and the index of that tile
         * in the array of all tiles */
        uint tile_x = scrolled_x / TILE_WIDTH_PX;
        uint tile_y = scrolled_y / TILE_HEIGHT_PX;

        /* Work out which specific (x,y) inside that tile we're going to render */
        uint tile_pixel_x = scrolled_x % TILE_WIDTH_PX;
        uint tile_pixel_y = scrolled_y % TILE_HEIGHT_PX;

        /* Work out the address of the tile ID from the tile map */
        uint tile_index = tile_y * TILES_PER_LINE + tile_x;
        Address tile_id_address = tile_map_address + tile_index;

        /* Grab the ID of the tile we'll get data from in the tile map */
        u8 tile_id = mmu.read(tile_id_address);

        /* Calculate the offset from the start of the tile data memory where
         * the data for our tile lives */
        uint tile_data_mem_offset = use_tile_set_zero
            ? tile_id * TILE_BYTES
            : (static_cast<s8>(tile_id) + 128) * TILE_BYTES;

        /* Calculate the extra offset to the data for the line of pixels we
         * are rendering from.
         * 2 (bytes per line of pixels) * y (lines) */
        uint tile_data_line_offset = tile_pixel_y * 2;

        Address tile_line_data_start_address = tile_set_address + tile_data_mem_offset + tile_data_line_offset;

        /* FIXME: We fetch the full line of pixels for each pixel in the tile
         * we render. This could be altered to work in a way that avoids re-fetching
         * for a more performant renderer */
        u8 pixels_1 = mmu.read(tile_line_data_start_address);
        u8 pixels_2 = mmu.read(tile_line_data_start_address + 1);

        DmgLogicalColor pixel_color = get_pixel_from_line(pixels_1, pixels_2, tile_pixel_x);
        DmgColor screen_color = get_color_from_palette(pixel_color, palette);

        dmg_buffer.set_pixel(screen_x, screen_y, screen_color);
    }
}

void Video::draw_sprite(const uint sprite_n) {
    using bitwise::check_bit;

    /* Each sprite is represented by 4 bytes, or 8 bytes in 8x16 mode */
    Address offset_in_oam = sprite_n * SPRITE_BYTES;

    Address oam_start = 0xFE00 + offset_in_oam.value();
    u8 sprite_y = mmu.read(oam_start);
    u8 sprite_x = mmu.read(oam_start + 1);

    /* If the sprite would be drawn offscreen, don't draw it */
    if (sprite_y == 0 || sprite_y >= 160) { return; }
    if (sprite_x == 0 || sprite_x >= 168) { return; }

    uint sprite_size_multiplier = sprite_size()
        ? 2 : 1;

    /* Sprites are always taken from the first tileset */
    Address tile_set_location = TILE_SET_ZERO_ADDRESS;

    u8 pattern_n = mmu.read(oam_start + 2);
    u8 sprite_attrs = mmu.read(oam_start + 3);

    /* Bits 0-3 are used only for CGB */
    bool use_palette_1 = check_bit(sprite_attrs, 4);
    bool flip_x = check_bit(sprite_attrs, 5);
    bool flip_y = check_bit(sprite_attrs, 6);
    bool obj_behind_bg = check_bit(sprite_attrs, 7);

    DmgPalette palette = use_palette_1
        ? load_palette(sprite_palette_1)
        : load_palette(sprite_palette_0);

    uint tile_offset = pattern_n * TILE_BYTES;

    Address pattern_address = tile_set_location + tile_offset;

    DmgTile tile(pattern_address, mmu, sprite_size_multiplier);
    int start_y = sprite_y - 16;
    int start_x = sprite_x - 8;

    for (uint y = 0; y < TILE_HEIGHT_PX * sprite_size_multiplier; y++) {
        for (uint x = 0; x < TILE_WIDTH_PX; x++) {
            uint maybe_flipped_y = !flip_y ? y : (TILE_HEIGHT_PX * sprite_size_multiplier) - y - 1;
            uint maybe_flipped_x = !flip_x ? x : TILE_WIDTH_PX - x - 1;

            DmgLogicalColor gb_color = tile.get_pixel(maybe_flipped_x, maybe_flipped_y);

            // Color 0 is transparent
            if (gb_color == DmgLogicalColor::Color0) { continue; }

            int screen_x = start_x + x;
            int screen_y = start_y + y;

            if (!is_on_screen(screen_x, screen_y)) { continue; }

            auto existing_pixel = dmg_buffer.get_pixel(screen_x, screen_y);

            // FIXME: We need to see if the color we're writing over is
            // logically Color0, rather than looking at the color after
            // the current palette has been applied
            if (obj_behind_bg && existing_pixel != DmgColor::White) { continue; }

            DmgColor screen_color = get_color_from_palette(gb_color, palette);

            dmg_buffer.set_pixel(screen_x, screen_y, screen_color);
        }
    }
}

DmgLogicalColor Video::get_pixel_from_line(u8 byte1, u8 byte2, u8 pixel_index) const {
    using bitwise::bit_value;

    u8 color_u8 = static_cast<u8>((bit_value(byte2, 7-pixel_index) << 1) | bit_value(byte1, 7-pixel_index));
    return get_color(color_u8);
}

bool Video::is_on_screen_x(u8 x) const {
    return x < GAMEBOY_WIDTH;
}

bool Video::is_on_screen_y(u8 y) const {
    return y < GAMEBOY_HEIGHT;
}

bool Video::is_on_screen(u8 x, u8 y) const {
    return is_on_screen_x(x) && is_on_screen_y(y);
}

DmgPalette Video::load_palette(ByteRegister& palette_register) const {
    using bitwise::compose_bits;
    using bitwise::bit_value;

    /* TODO: Reduce duplication */
    u8 color0 = compose_bits(bit_value(palette_register.value(), 1), bit_value(palette_register.value(), 0));
    u8 color1 = compose_bits(bit_value(palette_register.value(), 3), bit_value(palette_register.value(), 2));
    u8 color2 = compose_bits(bit_value(palette_register.value(), 5), bit_value(palette_register.value(), 4));
    u8 color3 = compose_bits(bit_value(palette_register.value(), 7), bit_value(palette_register.value(), 6));

    DmgColor real_color_0 = get_real_color(color0);
    DmgColor real_color_1 = get_real_color(color1);
    DmgColor real_color_2 = get_real_color(color2);
    DmgColor real_color_3 = get_real_color(color3);

    return { real_color_0, real_color_1, real_color_2, real_color_3 };
}

DmgColor Video::get_color_from_palette(DmgLogicalColor color, const DmgPalette& palette) {
    switch (color) {
        case DmgLogicalColor::Color0: return palette.color0;
        case DmgLogicalColor::Color1: return palette.color1;
        case DmgLogicalColor::Color2: return palette.color2;
        case DmgLogicalColor::Color3: return palette.color3;
    }
}


DmgColor Video::get_real_color(u8 pixel_value) const {
    switch (pixel_value) {
        case 0: return DmgColor::White;
        case 1: return DmgColor::LightGray;
        case 2: return DmgColor::DarkGray;
        case 3: return DmgColor::Black;
        default:
            fatal_error("Invalid color value");
    }
}

void Video::set_vram_bank(u8 value) {
    video_ram_bank.set(value & 0b1);
}

u8 Video::get_vram_bank() const {
    return video_ram_bank.value();
}

u16 Video::calculate_vram_address(const Address& address) const {
    if (model == Model::Dmg) {
        return address.value();
    }

    u16 offset = 0x2000 * video_ram_bank.value();
    return address.value() + offset;
}

void Video::register_vblank_callbacks(
    const dmg_vblank_callback_t& _dmg_vblank_callback,
    const cgb_vblank_callback_t& _cgb_vblank_callback
) {
    dmg_vblank_callback = _dmg_vblank_callback;
    cgb_vblank_callback = _cgb_vblank_callback;
}

void Video::draw() {
    if (model == Model::Dmg) {
        dmg_vblank_callback(dmg_buffer);
    } else {
        cgb_vblank_callback(cgb_buffer);
    }
}
