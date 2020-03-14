#include "color.h"
#include "../util/log.h"

PaletteIndex get_color(u8 pixel_value) {
    switch (pixel_value) {
        case 0:
            return PaletteIndex::Color0;
        case 1:
            return PaletteIndex::Color1;
        case 2:
            return PaletteIndex::Color2;
        case 3:
            return PaletteIndex::Color3;
        default:
            fatal_error("Invalid color value: %d", pixel_value);
    }
}

DmgColor get_color_from_palette(PaletteIndex color, const DmgPalette& palette) {
    switch (color) {
        case PaletteIndex::Color0: return palette.color0;
        case PaletteIndex::Color1: return palette.color1;
        case PaletteIndex::Color2: return palette.color2;
        case PaletteIndex::Color3: return palette.color3;
    }
}

CgbColor get_color_from_palette(PaletteIndex color, const CgbPalette& palette) {
    switch (color) {
        case PaletteIndex::Color0: return palette.color0;
        case PaletteIndex::Color1: return palette.color1;
        case PaletteIndex::Color2: return palette.color2;
        case PaletteIndex::Color3: return palette.color3;
    }
}
