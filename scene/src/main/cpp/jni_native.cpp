//
// Created by 龚喜 on 2024/8/18.
//
#include "jni_native.h"
#include <system_error>
#include "roam_renderer.h"
#include "native_roam_view.h"
#include "logger.h"
void registerNatives(JavaVM* vm) {
    theJVM = vm;
    jni::JNIEnv& env = jni::GetEnv(*vm, jni::jni_version_1_6);

    Logger::registerNative(env);
//    SceneRender::registerNative(env);
    RoamRenderer::registerNative(env);
    NativeRoamView::registerNative(env);
}


void unregisterNatives(JavaVM* vm) {
}
