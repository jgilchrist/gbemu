#include "log.h"

#include "string.h"

Logger log;
const char* COLOR_TRACE = "\033[1;30m";
const char* COLOR_DEBUG = "\033[1;37m";
const char* COLOR_INFO = "\033[1;34m";
const char* COLOR_WARNING = "\033[1;33m";
const char* COLOR_ERROR = "\033[1;31m";
const char* COLOR_RESET = "\033[0m";

Logger::Logger() {}

void Logger::log(LogLevel level, const std::string file, int line, const char* fmt, ...) {
    if (!should_log(level)) {
        return;
    }

    va_list args;
    va_start(args, fmt);
    std::string msg = str_format(fmt, args);
    va_end(args);

    std::string fileinfo = log_filename ? str_format(" (%s:%d)", file.c_str(), line) : "";

    fprintf((level < LogLevel::Error) ? stdout : stderr,
        "%s|%s %s%s\n",
        level_color(level), fileinfo.c_str(), COLOR_RESET, msg.c_str());
}

void Logger::set_level(LogLevel level) {
    current_level = level;
}

bool Logger::should_log(LogLevel level) const {
    return enabled && (current_level <= level);
}

inline const char* Logger::level_color(LogLevel level) const {
    switch (level) {
        case LogLevel::Trace:
            return COLOR_TRACE;
        case LogLevel::Debug:
            return COLOR_DEBUG;
        case LogLevel::Info:
            return COLOR_INFO;
        case LogLevel::Warning:
            return COLOR_WARNING;
        case LogLevel::Error:
            return COLOR_ERROR;
    }
}

void log_set_level(LogLevel level) {
    log.set_level(level);
}
