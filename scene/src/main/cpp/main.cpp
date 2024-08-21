//
// Created by 龚喜 on 2024/8/18.
//
#pragma once
#include <cassert>
#include "jni.h"
#include "jni_native.h"

extern "C"
JNIEXPORT jint JNI_OnLoad(JavaVM *vm, void *reserved) {
    assert(vm != nullptr);
    registerNatives(vm);
    return JNI_VERSION_1_6;
}


extern "C"
JNIEXPORT void JNI_OnUnload(JavaVM *vm, void *reserved) {
    assert(vm != nullptr);
    unregisterNatives(vm);
}

