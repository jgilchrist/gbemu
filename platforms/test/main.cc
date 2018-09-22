#include "../../src/gameboy_prelude.h"

static std::unique_ptr<Gameboy> gameboy;

static void draw(const FrameBuffer& buffer) {
}

static bool is_closed() {
    return false;
}

int main(int argc, char* argv[]) {
    Options options = get_options(argc, argv);
    log_set_level(get_log_level(options));

    Cartridge cartridge(options.filename);

    gameboy = std::make_unique<Gameboy>(cartridge, options);

    gameboy->run(&is_closed, &draw);
}
