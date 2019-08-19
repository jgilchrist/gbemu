#include "../../src/gameboy_prelude.h"
#include "../cli/cli.h"

static std::unique_ptr<Gameboy> gameboy;

static void draw(const FrameBuffer& buffer) {
}

static bool is_closed() {
    return false;
}

int main(int argc, char* argv[]) {
    CliOptions cliOptions = get_cli_options(argc, argv);
    auto rom_data = read_bytes(cliOptions.filename);
    gameboy = std::make_unique<Gameboy>(Model::Cgb, rom_data, cliOptions.options);
    gameboy->run(&is_closed, &draw, &draw);
}
