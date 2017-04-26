#include "gameboy.h"
#include "cartridge.h"
#include "video/screen.h"
#include "video/screens.h"
#include "util/cli.h"
#include "util/log.h"

#include <memory>

int main(int argc, char* argv[]) {
    Options options = get_options(argc, argv);
    log_set_level(get_log_level(options));

    Cartridge cartridge(options.filename);
    auto screen = get_screen(options.headless, options.show_full_framebuffer);

    Gameboy gameboy(screen, cartridge, options.debugger);
    gameboy.run();
}
