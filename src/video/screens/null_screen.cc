#include "null_screen.h"

void NullScreen::draw(const FrameBuffer& buffer, const uint scrollx, const uint scrolly, const BGPalette& bg_palette) {
    unused(buffer, scrollx, scrolly, bg_palette);
    return;
}

bool NullScreen::is_open() {
    return true;
}
