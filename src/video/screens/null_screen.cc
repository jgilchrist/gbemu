#include "null_screen.h"

void NullScreen::draw(const FrameBuffer& buffer) {
    return;
}

bool NullScreen::is_open() {
    return true;
}
