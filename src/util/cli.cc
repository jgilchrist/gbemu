#include "cli.h"
#include "../definitions.h"

bool flag_set(char** begin, char** end, const std::string& short_option, const std::string& long_option) {
    bool short_option_found = std::find(begin, end, short_option) != end;
    bool long_option_found = std::find(begin, end, long_option) != end;
    return short_option_found || long_option_found;
}

Options get_options(int argc, char* argv[]) {
    char** begin = argv;
    char** end = argv + argc;

    if (argc < 2) {
        fatal_error("Please provide a ROM file to run");
    }

    bool debugger = flag_set(begin, end, "-d", "--debug");
    bool trace = flag_set(begin, end, "-t", "--trace");
    bool disable_logs = flag_set(begin, end, "-n", "--nolog");
    bool show_full_framebuffer = flag_set(begin, end, "-f", "--framebuffer");

    std::string filename = argv[1];

    return Options { debugger, trace, disable_logs, show_full_framebuffer, filename };
}

LogLevel get_log_level(Options& options) {
    if (options.disable_logs) return LogLevel::Error;

    auto log_level = options.trace
        ? LogLevel::Trace
        : LogLevel::Debug;

    return log_level;
}
