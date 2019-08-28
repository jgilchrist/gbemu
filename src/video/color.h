#pragma once

#include "../definitions.h"

enum class DmgLogicalColor {
    Color0, /* White */
    Color1, /* Light gray */
    Color2, /* Dark gray */
    Color3, /* Black */
};

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

DmgLogicalColor get_color(u8 pixel_value);

class CgbColor {
};
