#include "gameboy.h"
#include "cartridge/cartridge.h"
#include "video/screen.h"
#include "video/screens/null_screen.h"
#include "video/screens/sfml_screen.h"
#include "util/cli.h"
#include "util/log.h"

#include <memory>

std::shared_ptr<Screen> get_screen(std::shared_ptr<Input> input, Options& options);
std::shared_ptr<Screen> get_screen(std::shared_ptr<Input> input, Options& options) {
    if (options.headless) {
        return std::make_shared<NullScreen>();
    }

    return std::make_shared<SFMLScreen>(input, options.show_full_framebuffer);
}

int main(int argc, char* argv[]) {
    Options options = get_options(argc, argv);
    log_set_level(get_log_level(options));

    Cartridge cartridge(options.filename);
    auto input = std::make_shared<Input>();
    auto screen = get_screen(input, options);

    Gameboy gameboy(screen, input, cartridge, options);
    gameboy.run();
}
