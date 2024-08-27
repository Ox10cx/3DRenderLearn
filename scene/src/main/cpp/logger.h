//
// Created by 龚喜 on 2024/8/23.
//

#ifndef ASSIMPDEMO_LOGGER_H
#define ASSIMPDEMO_LOGGER_H

#include <jni/jni.hpp>
#include "roamgl/utils/event.h"

class Logger {
public:
    static constexpr auto Name() {
        return "com/gx/kotlin/scene/log/Logger";
    };

    static void registerNative(jni::JNIEnv&);

    static void log(jni::JNIEnv&, EventSeverity severity, const std::string& msg);

};


#endif //ASSIMPDEMO_LOGGER_H
