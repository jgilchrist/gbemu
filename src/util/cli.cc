#include "cli.h"
#include "../definitions.h"

#include <vector>

void set_options(std::string& flag, Options& options) {
    if (flag == "--debug") { options.debugger = true; return; }
    if (flag == "--trace") { options.trace = true; return; }
    if (flag == "--silent") { options.disable_logs = true; return; }
    if (flag == "--headless") { options.headless = true; return; }
    if (flag == "--whole-framebuffer") { options.show_full_framebuffer = true; return; }
    if (flag == "--exit-on-infinite-jr") { options.exit_on_infinite_jr = true; return; }

    fatal_error("Unknown flag: %s", flag.c_str());
}

Options get_options(int argc, char* argv[]) {
    if (argc < 2) {
        fatal_error("Please provide a ROM file to run");
    }

    Options options;
    options.filename = argv[1];

    std::vector<std::string> flags(argv + 2, argv + argc);

    for (std::string& flag : flags) {
        set_options(flag, options);
    }

    return options;
}

LogLevel get_log_level(Options& options) {
    if (options.disable_logs) return LogLevel::Error;

    auto log_level = options.trace
        ? LogLevel::Trace
        : LogLevel::Debug;

    return log_level;
}
