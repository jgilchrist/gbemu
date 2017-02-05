#pragma once

#include "../definitions.h"

#include <vector>

const uint FRAMEBUFFER_SIZE = 255;

class FrameBuffer {
public:
    FrameBuffer(uint width, uint height);

    void set_pixel(uint x, uint y, GBColor color);
    GBColor get_pixel(uint x, uint y) const;

private:
    uint width;
    uint height;

    uint pixel_index(uint x, uint y) const;

    std::vector<GBColor> buffer;
};
