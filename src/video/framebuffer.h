#pragma once

#include "../definitions.h"

#include <vector>

class FrameBuffer {
public:
    FrameBuffer(uint width, uint height);

    void set_pixel(uint x, uint y, Color color);
    Color get_pixel(uint x, uint y) const;

    void reset();

private:
    uint width;
    uint height;

    uint pixel_index(uint x, uint y) const;

    std::vector<Color> buffer;
};
