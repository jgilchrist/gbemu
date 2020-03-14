#pragma once

#include "../definitions.h"

enum class DmgColor {
    White,
    LightGray,
    DarkGray,
    Black,
};

struct DmgPalette {
    DmgColor color0 = DmgColor::White;
    DmgColor color1 = DmgColor::LightGray;
    DmgColor color2 = DmgColor::DarkGray;
    DmgColor color3 = DmgColor::Black;
};

struct CgbColor {
    u8 r;
    u8 g;
    u8 b;
};

struct CgbPalette {
    CgbColor color0;
    CgbColor color1;
    CgbColor color2;
    CgbColor color3;
};

enum class PaletteIndex {
    Color0,
    Color1,
    Color2,
    Color3,
};

PaletteIndex get_color(u8 pixel_value);
DmgColor get_color_from_palette(PaletteIndex color, const DmgPalette& palette);
CgbColor get_color_from_palette(PaletteIndex color, const CgbPalette& palette);
