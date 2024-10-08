//
// Created by 龚喜 on 2024/8/22.
//

#ifndef ASSIMPDEMO_LOG_H
#define ASSIMPDEMO_LOG_H


#include "event.h"
#include <string>

class Log {

private:
    template <typename T, size_t N>
    constexpr static bool includes(const T e, const T (&l)[N], const size_t i = 0) {
        return i < N && (l[i] == e || includes(e, l, i + 1));
    }


public:
    template <typename ...Args>
    static void Debug(Event event, Args&& ...args) {
        Record(EventSeverity::Debug, event, ::std::forward<Args>(args)...);
    }

    template <typename ...Args>
    static void Info(Event event, Args&& ...args) {
        Record(EventSeverity::Info, event, ::std::forward<Args>(args)...);
    }

    template <typename ...Args>
    static void Warning(Event event, Args&& ...args) {
        Record(EventSeverity::Warning, event, ::std::forward<Args>(args)...);
    }

    template <typename ...Args>
    static void Error(Event event, Args&& ...args) {
        Record(EventSeverity::Error, event, ::std::forward<Args>(args)...);
    }

    template <typename ...Args>
    static void Record(EventSeverity severity, Event event, Args&& ...args) {
        if (!includes(severity, disabledEventSeverities) &&
            !includes(event, disabledEvents) &&
            !includes({ severity, event }, disabledEventPermutations)) {
            record(severity, event, ::std::forward<Args>(args)...);
        }
    }

private:
    static std::string getCurrentThreadName();

    static void record(EventSeverity severity, Event event, const std::string &msg);
    static void record(EventSeverity severity, Event event, const char* format = "", ...);
    static void record(EventSeverity severity, Event event, int64_t code, const char* format = "", ...);
    static void record(EventSeverity severity, Event event, int64_t code, const std::string &msg);

    // This method is the data sink that must be implemented by each platform we
    // support. It should ideally output the error message in a human readable
    // format to the developer.
    static void platformRecord(EventSeverity severity, const std::string &msg);

};



#endif //ASSIMPDEMO_LOG_H
