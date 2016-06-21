#include <cstdio>

#include "gameboy.h"
#include "cartridge.h"
#include "video/screen.h"
#include "util/log.h"

#include "video/screens/null_screen.h"
#include "video/screens/sfml_screen.h"

int main(int argc, char* argv[]) {
    if (argc != 2) {
        log_error("Please provide a ROM file to run")
        return 0;
    }

    log_set_level(LogLevel::Trace);

    std::string rom_name = argv[1];
    log_info("Loading rom from file: %s", rom_name.c_str());

    Cartridge cartridge(rom_name);
    SFMLScreen screen;
    Gameboy gameboy(screen, cartridge);

    gameboy.run();
}
