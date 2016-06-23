#include "video_mode.h"

void VideoModeManager::tick(Cycles cycles) {
    cycle_counter += cycles.cycles;
}
