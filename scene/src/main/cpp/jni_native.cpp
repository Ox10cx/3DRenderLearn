//
// Created by 龚喜 on 2024/8/18.
//
#include "jni_native.h"
#include <system_error>
#include "RenderLogger.h"
#include "RoamRender.h"
#include "NativeRoamView.h"
void registerNatives(JavaVM* vm) {
    theJVM = vm;
    jni::JNIEnv& env = jni::GetEnv(*vm, jni::jni_version_1_6);

//    SceneRender::registerNative(env);
    RoamRender::registerNative(env);
    NativeRoamView::registerNative(env);
    LOGE( "GetEnv Success");
}


void unregisterNatives(JavaVM* vm) {
    LOGI( "unregisterNatives");
}
