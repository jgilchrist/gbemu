#include "null_screen.h"

void NullScreen::draw(const FrameBuffer& buffer, const BGPalette& bg_palette) {
    unused(buffer, bg_palette);
    return;
}

bool NullScreen::is_open() {
    return true;
}
