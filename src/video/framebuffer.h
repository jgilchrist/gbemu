#pragma once

#include "../definitions.h"

class FrameBuffer {
public:
    FrameBuffer();

    void set_pixel(uint x, uint y, Color color);
    Color get_pixel(uint x, uint y) const;

private:
    uint pixel_index(uint x, uint y) const;

    Color buffer[GAMEBOY_HEIGHT*GAMEBOY_WIDTH];
};
