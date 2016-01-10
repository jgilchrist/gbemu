#include "string.h"

#include <cstdio>

std::string str_format(const char* fmt, va_list args) {
    char buf[8192];
    vsnprintf(buf, 8192, fmt, args);
    return std::string(buf);
}

std::string str_format(const char* fmt, ...) {
    char buf[8192];
    va_list args;

    va_start(args, fmt);
    vsnprintf(buf, 8192, fmt, args);
    va_end(args);

    return std::string(buf);
}
