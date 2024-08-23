//
// Created by 龚喜 on 2024/8/23.
//

#include "log.h"
#include "enum.h"


#include <cstdio>
#include <cstdarg>
#include <sstream>

#include <sys/prctl.h>



std::string Log::getCurrentThreadName() {
    char name[32] = "unknown";

    if (prctl(PR_GET_NAME, name) == -1) {
        Log::Warning(Event::General, "Couldn't get thread name");
    }

    return name;
}

void Log::record(EventSeverity severity, Event event, const std::string &msg) {
    record(severity, event, -1, msg);
}

void Log::record(EventSeverity severity, Event event, const char* format, ...) {
    va_list args;
    va_start(args, format);
    char msg[4096];
    vsnprintf(msg, sizeof(msg), format, args);
    va_end(args);

    record(severity, event, -1, std::string{ msg });
}

void Log::record(EventSeverity severity, Event event, int64_t code, const char* format, ...) {
    va_list args;
    va_start(args, format);
    char msg[4096];
    vsnprintf(msg, sizeof(msg), format, args);
    va_end(args);

    record(severity, event, code, std::string{ msg });
}

void Log::record(EventSeverity severity, Event event, int64_t code, const std::string &msg) {

    std::stringstream logStream;

    logStream << "{" << getCurrentThreadName() << "}";
    logStream << "[" << Enum<Event>::toString(event) << "]";

    if (code >= 0) {
        logStream << "(" << code << ")";
    }

    if (!msg.empty()) {
        logStream << ": " << msg;
    }

    platformRecord(severity, logStream.str());
}