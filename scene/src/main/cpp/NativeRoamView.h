//
// Created by 龚喜 on 2024/8/19.
//

#ifndef ASSIMPDEMO_NATIVEROAMVIEW_H
#define ASSIMPDEMO_NATIVEROAMVIEW_H


#include <jni/jni.hpp>

class NativeRoamView {
public:
    static constexpr auto Name() { return "com/gx/kotlin/scene/roam/NativeRoamView"; };

    static void registerNative(JNIEnv& env);

    NativeRoamView(jni::JNIEnv& _env, const jni::Object<NativeRoamView>&);

    ~NativeRoamView();

private:
    void moveBy(jni::JNIEnv&, jni::jdouble, jni::jdouble, jni::jlong);

    void setBearingXY(jni::JNIEnv&, jni::jdouble, jni::jdouble, jni::jdouble, jni::jlong);

    void setPitch(jni::JNIEnv&, jni::jdouble, jni::jlong);

    void setZoom(jni::JNIEnv&, jni::jdouble, jni::jdouble, jni::jdouble, jni::jlong);

};


#endif //ASSIMPDEMO_NATIVEROAMVIEW_H
