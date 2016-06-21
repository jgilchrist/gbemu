#include "framebuffer.h"

FrameBuffer::FrameBuffer() {
}

void FrameBuffer::set_pixel(int x, int y, Color color) {
    buffer[pixel_index(x, y)] = color;
}

Color FrameBuffer::get_pixel(int x, int y) const {
    return buffer[pixel_index(x, y)];
}

inline int FrameBuffer::pixel_index(int x, int y) const {
    return (y * GAMEBOY_HEIGHT) + x;
}
