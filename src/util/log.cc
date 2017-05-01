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

#include "log.h"

#include "string.h"

Logger log;
const char* COLOR_TRACE = "\033[1;30m";
const char* COLOR_DEBUG = "\033[1;37m";
const char* COLOR_UNIMPLEMENTED = "\033[1;35m";
const char* COLOR_INFO = "\033[1;34m";
const char* COLOR_WARNING = "\033[1;33m";
const char* COLOR_ERROR = "\033[1;31m";
const char* COLOR_RESET = "\033[0m";

Logger::Logger() {}

void Logger::log(LogLevel level, const char* fmt, ...) {
    if (!should_log(level)) {
        return;
    }

    va_list args;
    va_start(args, fmt);
    std::string msg = str_format(fmt, args);
    va_end(args);

    fprintf((level < LogLevel::Error) ? stdout : stderr,
        "%s| %s%s\n",
        level_color(level), COLOR_RESET, msg.c_str());
}

void Logger::set_level(LogLevel level) {
    current_level = level;
}

void Logger::enable_tracing() {
    tracing_enabled = true;
}

bool Logger::should_log(LogLevel level) const {
    if (!tracing_enabled && level == LogLevel::Trace) { return false; }

    return enabled && (current_level <= level);
}

inline const char* Logger::level_color(LogLevel level) const {
    switch (level) {
        case LogLevel::Trace:
            return COLOR_TRACE;
        case LogLevel::Debug:
            return COLOR_DEBUG;
        case LogLevel::Unimplemented:
            return COLOR_UNIMPLEMENTED;
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
