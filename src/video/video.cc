#include "video.h"

Video::Video(MMU& inMMU) :
    mmu(inMMU)
{
}

const FrameBuffer& Video::get_framebuffer() {
    return frame_buffer;
}
