#pragma once

#include "../../src/options.h"
#include <vector>

struct CliOptions {
    Options options;
    std::string filename;
};

CliOptions get_cli_options(int argc, char* argv[]);
CliOptions get_cli_options(int argc, char* argv[]) {
    if (argc < 2) {
        fatal_error("Please provide a ROM file to run");
    }

    CliOptions cliOptions;
    cliOptions.filename = argv[1];

    std::vector<std::string> flags(argv + 2, argv + argc);

    for (std::string& flag : flags) {
        if (flag == "--debug") { cliOptions.options.debugger = true; }
        if (flag == "--trace") { cliOptions.options.trace = true; }
        if (flag == "--silent") { cliOptions.options.disable_logs = true; }
        if (flag == "--headless") { cliOptions.options.headless = true; }
        if (flag == "--whole-framebuffer") { cliOptions.options.show_full_framebuffer = true; }
        if (flag == "--exit-on-infinite-jr") { cliOptions.options.exit_on_infinite_jr = true; }
        if (flag == "--print-serial") { cliOptions.options.print_serial = true; }

        fatal_error("Unknown flag: %s", flag.c_str());
    }

    return cliOptions;
}
