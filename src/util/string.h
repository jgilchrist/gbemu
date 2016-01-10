#pragma once

#include <string>

std::string str_format(const char* fmt, va_list args);
std::string str_format(const char* fmt, ...);
