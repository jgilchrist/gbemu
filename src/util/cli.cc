#include "cli.h"
#include "../definitions.h"

bool flag_set(char** begin, char** end, const std::string& long_option) {
    return std::find(begin, end, long_option) != end;
}

Options get_options(int argc, char* argv[]) {
    char** begin = argv;
    char** end = argv + argc;

    if (argc < 2) {
        fatal_error("Please provide a ROM file to run");
    }

    bool debugger = flag_set(begin, end, "--debug");
    bool trace = flag_set(begin, end, "--trace");
    bool disable_logs = flag_set(begin, end, "--nolog");
    bool headless = flag_set(begin, end, "--headless");
    bool show_full_framebuffer = flag_set(begin, end, "--full-framebuffer");

    std::string filename = argv[1];

    return Options { debugger, trace, disable_logs, headless, show_full_framebuffer, filename };
}

LogLevel get_log_level(Options& options) {
    if (options.disable_logs) return LogLevel::Error;

    auto log_level = options.trace
        ? LogLevel::Trace
        : LogLevel::Debug;

    return log_level;
}
