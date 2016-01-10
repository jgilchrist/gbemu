#ifndef EMULATOR_STRING_H
#define EMULATOR_STRING_H

#include <string>

std::string str_format(const char* fmt, va_list args);
std::string str_format(const char* fmt, ...);

#endif
