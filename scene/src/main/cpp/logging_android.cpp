//
// Created by 龚喜 on 2024/8/23.
//
#include "attach_env.h"
#include "roamgl/utils/log.h"
#include "logger.h"

void Log::platformRecord(EventSeverity severity, const std::string &msg) {
    auto env{ android::AttachEnv() };
    Logger::log(*env, severity, msg);
}