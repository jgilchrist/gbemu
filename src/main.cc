#include "gameboy.h"
#include "cartridge.h"
#include "video/screen.h"
#include "util/log.h"

#include "video/screens/null_screen.h"
#include "video/screens/sfml_screen.h"

int main(int argc, char* argv[]) {
    log_set_level(LogLevel::Info);

    if (argc < 2) {
        log_error("Please provide a ROM file to run")
        return 1;
    }

    bool should_debug = (argc == 3);
    if (should_debug) {
        log_info("Enabling debugger...");
    }

    std::string rom_name = argv[1];
    Cartridge cartridge(rom_name);

    SFMLScreen screen;

    Gameboy gameboy(screen, cartridge, should_debug);
    gameboy.run();
}
