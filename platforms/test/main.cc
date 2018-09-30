#include "../../src/gameboy_prelude.h"

static std::unique_ptr<Gameboy> gameboy;

static void draw(const FrameBuffer& buffer) {
}

static bool is_closed() {
    return false;
}

int main(int argc, char* argv[]) {
    Options options = get_options(argc, argv);
    auto rom_data = read_bytes(options.filename);
    gameboy = std::make_unique<Gameboy>(rom_data, options);
    gameboy->run(&is_closed, &draw);
}
