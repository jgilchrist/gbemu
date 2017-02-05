#include "gameboy.h"
#include "cartridge.h"
#include "video/screen.h"
#include "util/cli.h"
#include "util/log.h"

#include "video/screens/null_screen.h"
#include "video/screens/sfml_screen.h"

int main(int argc, char* argv[]) {
    Options options = get_options(argc, argv);
    log_set_level(get_log_level(options));

    Cartridge cartridge(options.filename);
    SFMLScreen screen(5, options.show_full_framebuffer);

    Gameboy gameboy(screen, cartridge, options.debugger);
    gameboy.run();
}
