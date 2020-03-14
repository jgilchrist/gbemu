#pragma once

#include "color.h"

#include <vector>

template <class TColor>
class FrameBuffer {
public:
    FrameBuffer(uint _width, uint _height) :
        width(_width),
        height(_height),
        buffer(width*height) {}

    void set_pixel(uint x, uint y, TColor color) {
        buffer[pixel_index(x, y)] = color;
    }

    TColor get_pixel(uint x, uint y) const {
        return buffer.at(pixel_index(x, y));
    }

    void reset() {
        for (uint i = 0; i < width * height; i++) {
            buffer[i] = {};
        }
    }

private:
    uint width;
    uint height;

    uint pixel_index(uint x, uint y) const {
        return (y * width) + x;
    }

    std::vector<TColor> buffer;
};

using DmgFrameBuffer = FrameBuffer<DmgColor>;
using CgbFrameBuffer = FrameBuffer<CgbColor>;
