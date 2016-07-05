#include "gameboy.h"
#include "cartridge.h"
#include "video/screen.h"
#include "util/log.h"

#include "video/screens/null_screen.h"
#include "video/screens/sfml_screen.h"

int main(int argc, char* argv[]) {
    log_set_level(LogLevel::Trace);

    if (argc != 2) {
        log_error("Please provide a ROM file to run")
        return 1;
    }

    std::string rom_name = argv[1];
    Cartridge cartridge(rom_name);

    SFMLScreen screen;

    Gameboy gameboy(screen, cartridge);
    gameboy.run();
}
