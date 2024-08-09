//
// Created by 龚喜 on 1/27/24.
//

#ifndef ASSIMPDEMO_RENDERLOGGER_H
#define ASSIMPDEMO_RENDERLOGGER_H

#include <android/log.h>

#define LOG_TAG "SceneRender"
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,   LOG_TAG, __VA_ARGS__)
#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,   LOG_TAG, __VA_ARGS__)
#define  LOGV(...)  __android_log_print(ANDROID_LOG_VERBOSE, LOG_TAG,__VA_ARGS__)
#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO   , LOG_TAG,__VA_ARGS__)
#define  LOGW(...)  __android_log_print(ANDROID_LOG_WARN   , LOG_TAG,__VA_ARGS__)
#define  LOGF(...)  __android_log_print(ANDROID_LOG_FATAL  , LOG_TAG,__VA_ARGS__)

#endif //ASSIMPDEMO_RENDERLOGGER_H
