#include "null_screen.h"

void NullScreen::clear() {
}

void NullScreen::process_events() {
}

void NullScreen::draw(const FrameBuffer& buffer) {
    unused(buffer);
    return;
}

bool NullScreen::is_open() {
    return true;
}
