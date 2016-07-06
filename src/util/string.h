#pragma once

#include <string>
#include <vector>

std::string str_format(const char* fmt, va_list args);
std::string str_format(const char* fmt, ...);

std::vector<std::string> split(std::string str, char delim=' ');
