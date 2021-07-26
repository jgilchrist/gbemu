#include "color.h"
#include "../util/log.h"

auto get_color(u8 pixel_value) -> GBColor {
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
