#include "gameboy.h"
#include "cartridge.h"
#include "video/screen.h"
#include "util/cli.h"
#include "util/log.h"

#include "video/screens/null_screen.h"
#include "video/screens/sfml_screen.h"

#include <memory>

std::shared_ptr<Screen> get_screen(Options& options) {
    if (options.headless) {
        return std::make_shared<NullScreen>();
    }

    return std::make_shared<SFMLScreen>(options.show_full_framebuffer);
}

int main(int argc, char* argv[]) {
    Options options = get_options(argc, argv);
    log_set_level(get_log_level(options));

    Cartridge cartridge(options.filename);
    auto screen = get_screen(options);

    Gameboy gameboy(screen, cartridge, options.debugger);
    gameboy.run();
}
