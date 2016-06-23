#include "video.h"

Video::Video(Screen& inScreen, MMU& inMMU) :
    screen(inScreen),
    mmu(inMMU)
{
}

void Video::tick(Cycles cycles) {
    video_mode.tick(cycles);
}
