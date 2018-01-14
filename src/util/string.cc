#include "string.h"

#include <cstdio>
#include <sstream>

#include <cstdarg>

using std::string;
using std::vector;

string str_format(const char* fmt, va_list args) {
    char buf[8192];
    vsnprintf(buf, 8192, fmt, args);
    return string(buf);
}

string str_format(const char* fmt, ...) {
    char buf[8192];
    va_list args;

    va_start(args, fmt);
    vsnprintf(buf, 8192, fmt, args);
    va_end(args);

    return string(buf);
}

vector<string> split(string str, char delim) {
    vector<string> elems;

    std::stringstream stream(str);
    string item;
    while (getline(stream, item, delim)) {
        elems.push_back(item);
    }

    return elems;
}
