#pragma once

/*
 * Copyright (C) 2015 Alex Smith
 *
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#include <string>

enum class LogLevel {
    Trace,
    Debug,
    Info,
    Warning,
    Error,
};

class Logger {
public:
    Logger();

    void log(LogLevel level, const std::string file, int line, const char* fmt, ...);
    void set_level(LogLevel level);

    void enable_tracing();

private:
    bool should_log(LogLevel level) const;
    const char* level_color(LogLevel level) const;

    LogLevel current_level = LogLevel::Debug;
    bool enabled = true;
    bool log_filename = false;
    bool tracing_enabled = false;
};

extern Logger log;
extern const char* COLOR_TRACE;
extern const char* COLOR_DEBUG;
extern const char* COLOR_INFO;
extern const char* COLOR_WARNING;
extern const char* COLOR_ERROR;
extern const char* COLOR_RESET;

#define SHORTFILENAME (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)

#define log_trace(fmt, ...) log.log(LogLevel::Trace, SHORTFILENAME, __LINE__, fmt, ##__VA_ARGS__);
#define log_debug(fmt, ...) log.log(LogLevel::Debug, SHORTFILENAME, __LINE__, fmt, ##__VA_ARGS__);
#define log_info(fmt, ...) log.log(LogLevel::Info, SHORTFILENAME, __LINE__, fmt, ##__VA_ARGS__);
#define log_warn(fmt, ...) log.log(LogLevel::Warning, SHORTFILENAME, __LINE__, fmt, ##__VA_ARGS__);
#define log_error(fmt, ...) log.log(LogLevel::Error, SHORTFILENAME, __LINE__, fmt, ##__VA_ARGS__);

extern void log_set_level(LogLevel level);
