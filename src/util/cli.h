#pragma once

#include "log.h"

struct Options {
    bool debugger = false;
    bool trace = false;
    bool disable_logs = false;
    bool headless = false;
    bool show_full_framebuffer = false;
    bool exit_on_infinite_jr = false;
    std::string filename;
};

void set_options(std::string& flag, Options& options);
Options get_options(int argc, char* argv[]);

LogLevel get_log_level(Options& options);
