#include "video.h"

Video::Video(Screen& inScreen, MMU& inMMU) :
    screen(inScreen),
    mmu(inMMU)
{
}

const FrameBuffer& Video::get_framebuffer() {
    return frame_buffer;
}
