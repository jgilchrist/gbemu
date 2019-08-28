#include "color.h"
#include "../util/log.h"

auto get_color(u8 pixel_value) -> DmgLogicalColor {
    switch (pixel_value) {
        case 0:
            return DmgLogicalColor::Color0;
        case 1:
            return DmgLogicalColor::Color1;
        case 2:
            return DmgLogicalColor::Color2;
        case 3:
            return DmgLogicalColor::Color3;
        default:
            fatal_error("Invalid color value: %d", pixel_value);
    }
}
