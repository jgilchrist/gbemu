#include "null_screen.h"

NullScreen::NullScreen()
{
}

NullScreen::~NullScreen() {
}

void NullScreen::draw(const FrameBuffer& buffer) {
    return;
}

bool NullScreen::is_open() {
    return true;
}
