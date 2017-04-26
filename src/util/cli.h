#include "log.h"

struct Options {
    bool debugger;
    bool trace;
    bool disable_logs;
    bool show_full_framebuffer;
    std::string filename;
};

bool flag_set(char** begin, char** end, const std::string& long_option);
Options get_options(int argc, char* argv[]);

LogLevel get_log_level(Options& options);
