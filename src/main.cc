#include <cstdio>

#include "gameboy.h"
#include "util/log.h"

int main(int argc, char* argv[]) {
    if (argc != 2) {
        log_error("Please provide a ROM file to run")
        return 0;
    }

    log_info("Hello world!");
}
