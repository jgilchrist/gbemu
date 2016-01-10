#ifndef EMULATOR_LOG_H
#define EMULATOR_LOG_H

#include <string>

enum class LogLevel {
    Debug,
    Info,
    Warning,
    Error,
};

class Logger {
public:
    Logger();

    void log(LogLevel level, const char* file, int line, const std::string msg);
    void set_level(LogLevel level);

private:
    bool should_log(LogLevel level) const;
    const char* level_color(LogLevel level) const;

    LogLevel current_level = LogLevel::Debug;
    bool enabled = true;
};

extern Logger log;
extern const char* COLOR_DEBUG;
extern const char* COLOR_INFO;
extern const char* COLOR_WARNING;
extern const char* COLOR_ERROR;

#define __FILENAME__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)

#define log_debug(msg) log.log(LogLevel::Debug, __FILENAME__, __LINE__, msg);
#define log_info(msg) log.log(LogLevel::Info, __FILENAME__, __LINE__, msg);
#define log_warn(msg) log.log(LogLevel::Warning, __FILENAME__, __LINE__, msg);
#define log_error(msg) log.log(LogLevel::Error, __FILENAME__, __LINE__, msg);

extern void log_set_level(LogLevel level);

#endif
