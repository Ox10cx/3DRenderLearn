//
// Created by 龚喜 on 2024/8/23.
//
#include "enum.h"
#include "event.h"

MBGL_DEFINE_ENUM(EventSeverity, {
    { EventSeverity::Debug, "DEBUG" },
    { EventSeverity::Info, "INFO" },
    { EventSeverity::Warning, "WARNING" },
    { EventSeverity::Error, "ERROR" },
    { EventSeverity(-1), "UNKNOWN" },
});

MBGL_DEFINE_ENUM(Event, {
    { Event::General, "General" },
    { Event::Shader, "Shader" },
    { Event::Render, "Render" },
    { Event::OpenGL, "OpenGL" },
    { Event::JNI, "JNI" },
    { Event::Android, "Android" },
    { Event(-1), "Unknown" },
});
