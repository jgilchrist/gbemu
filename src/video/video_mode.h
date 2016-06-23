#pragma once

#include "../cycles.h"

const int CLOCKS_PER_HBLANK = 204; /* Mode 0 */
const int CLOCKS_PER_SCANLINE_OAM = 80; /* Mode 2 */
const int CLOCKS_PER_SCANLINE_VRAM = 172; /* Mode 3 */
const int CLOCKS_PER_SCANLINE = (CLOCKS_PER_SCANLINE_OAM + CLOCKS_PER_SCANLINE_VRAM + CLOCKS_PER_HBLANK);

const int CLOCKS_PER_VBLANK = 4560; /* Mode 1 */
const int SCANLINES_PER_FRAME = 144;
const int CLOCKS_PER_FRAME = (CLOCKS_PER_SCANLINE * SCANLINES_PER_FRAME) + CLOCKS_PER_VBLANK;


enum class VideoMode {
    ACCESS_OAM,
    ACCESS_VRAM,
    HBLANK,
    VBLANK,
};

class VideoModeManager {
public:
    void tick(Cycles cycles);

private:
    unsigned cycle_counter;
};
