#pragma once

#include <string>
#include <vector>

auto str_format(const char* fmt, va_list args) -> std::string;
auto str_format(const char* fmt, ...) -> std::string;

auto split(const std::string& str, char delim = ' ') -> std::vector<std::string>;
