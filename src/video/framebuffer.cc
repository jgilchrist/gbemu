#include "framebuffer.h"

FrameBuffer::FrameBuffer(uint _width, uint _height) :
    width(_width),
    height(_height),
    buffer(width*height, GBColor::Color0)
{
}

void FrameBuffer::set_pixel(uint x, uint y, GBColor color) {
    buffer[pixel_index(x, y)] = color;
}

GBColor FrameBuffer::get_pixel(uint x, uint y) const {
    return buffer.at(pixel_index(x, y));
}

inline uint FrameBuffer::pixel_index(uint x, uint y) const {
    return (y * height) + x;
}
