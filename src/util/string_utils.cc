#include "string_utils.h"

#include <cstdio>
#include <sstream>

#include <cstdarg>

using std::string;
using std::vector;

auto str_format(const char* fmt, va_list args) -> string {
    char buf[8192];
    vsnprintf(buf, 8192, fmt, args);
    return string(buf);
}

auto str_format(const char* fmt, ...) -> string {
    char buf[8192];
    va_list args;

    va_start(args, fmt);
    vsnprintf(buf, 8192, fmt, args);
    va_end(args);

    return string(buf);
}

auto split(string str, char delim) -> vector<string> {
    vector<string> elems;

    std::stringstream stream(str);
    string item;
    while (getline(stream, item, delim)) {
        elems.push_back(item);
    }

    return elems;
}
