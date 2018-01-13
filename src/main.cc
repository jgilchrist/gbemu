#include "gameboy.h"
#include "cartridge/cartridge.h"
#include "video/screen.h"
#include "video/screens.h"
#include "util/cli.h"
#include "util/log.h"

#include <memory>

int main(int argc, char* argv[]) {
    Options options = get_options(argc, argv);
    log_set_level(get_log_level(options));

    Cartridge cartridge(options.filename);
    auto input = std::make_shared<Input>();
    auto screen = get_screen(input, options);

    Gameboy gameboy(screen, input, cartridge, options);
    gameboy.run();
}
