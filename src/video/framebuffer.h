#pragma once

#include "video.h"

class FrameBuffer {
public:
    FrameBuffer();

    void set_pixel(int x, int y, Color color);
    Color get_pixel(int x, int y) const;

private:
    int pixel_index(int x, int y) const;

    Color buffer[GAMEBOY_HEIGHT*GAMEBOY_WIDTH];
};
