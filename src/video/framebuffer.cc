#include "framebuffer.h"

FrameBuffer::FrameBuffer(uint _width, uint _height) :
    width(_width),
    height(_height),
    buffer(width*height, Color::White)
{
}

void FrameBuffer::set_pixel(uint x, uint y, Color color) {
    buffer[pixel_index(x, y)] = color;
}

auto FrameBuffer::get_pixel(uint x, uint y) const -> Color { return buffer.at(pixel_index(x, y)); }

inline auto FrameBuffer::pixel_index(uint x, uint y) const -> uint { return (y * width) + x; }

void FrameBuffer::reset() {
    for (uint i = 0; i < width * height; i++) {
        buffer[i] = Color::White;
    }
}
