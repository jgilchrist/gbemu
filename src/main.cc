#include "gameboy.h"
#include "cartridge.h"
#include "video/screen.h"
#include "util/log.h"

#include "video/screens/null_screen.h"
#include "video/screens/sfml_screen.h"

struct Options {
    bool debugger;
    bool trace;
    bool disable_logs;
    std::string filename;
};

static bool flag_set(char** begin, char** end, const std::string& short_option, const std::string& long_option) {
    bool short_option_found = std::find(begin, end, short_option) != end;
    bool long_option_found = std::find(begin, end, long_option) != end;
    return short_option_found || long_option_found;
}

static Options get_options(int argc, char* argv[]) {
    char** begin = argv;
    char** end = argv + argc;

    if (argc < 2) {
        log_error("Please provide a ROM file to run");
        fatal_error();
    }

    bool debugger = flag_set(begin, end, "-d", "--debug");
    bool trace = flag_set(begin, end, "-t", "--trace");
    bool disable_logs = flag_set(begin, end, "-n", "--nolog");

    std::string filename = argv[1];

    return Options { debugger, trace, disable_logs, filename };
}

int main(int argc, char* argv[]) {
    Options options = get_options(argc, argv);

    auto log_level = options.trace ?
        LogLevel::Trace : LogLevel::Debug;

    log_set_level(log_level);

    if (options.disable_logs) log_set_level(LogLevel::Error);

    Cartridge cartridge(options.filename);
    SFMLScreen screen;

    Gameboy gameboy(screen, cartridge, options.debugger);
    gameboy.run();
}
