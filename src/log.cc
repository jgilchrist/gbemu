#include "log.h"

#include <ctime>

Logger log;
const char* COLOR_DEBUG = "\033[1;30m";
const char* COLOR_INFO = "\033[1;34m";
const char* COLOR_WARNING = "\033[1;33m";
const char* COLOR_ERROR = "\033[1;31m";

Logger::Logger() {}

void Logger::log(LogLevel level, const char* file, int line, const std::string msg) {
    if (!should_log(level)) {
        return;
    }

    time_t t = time(nullptr);
    struct tm local;
    localtime_r(&t, &local);

    char timeString[10];
    strftime(timeString, 10, "%H:%M:%S", &local);

    fprintf((level < LogLevel::Error) ? stdout : stderr,
        "%s%s \033[0m%s (%s:%d)\n",
        level_color(level), timeString, msg.c_str(), file, line);
}

void Logger::set_level(LogLevel level) {
    current_level = level;
}

bool Logger::should_log(LogLevel level) const {
    return enabled && (current_level <= level);
}

inline const char* Logger::level_color(LogLevel level) const {
    switch (level) {
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
