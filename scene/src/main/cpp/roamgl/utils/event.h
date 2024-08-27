//
// Created by 龚喜 on 2024/8/22.
//

#ifndef ASSIMPDEMO_EVENT_H
#define ASSIMPDEMO_EVENT_H

#include <cstdint>

enum class EventSeverity : uint8_t {
    Debug,
    Info,
    Warning,
    Error,
};

enum class Event : uint8_t {
    General,
    Shader,
    Render,
    OpenGL,
    JNI,
    Android,
    File,
};

struct EventPermutation {
    const EventSeverity severity;
    const Event event;

    constexpr bool operator==(const EventPermutation &rhs) const {
        return severity == rhs.severity && event == rhs.event;
    }
};

constexpr EventSeverity disabledEventSeverities[] = {
        EventSeverity(-1) // Avoid zero size array
};

constexpr Event disabledEvents[] = {
        Event(-1) // Avoid zero size array
};

constexpr EventPermutation disabledEventPermutations[] = {
        { EventSeverity::Debug, Event::Shader }
};




#endif //ASSIMPDEMO_EVENT_H
