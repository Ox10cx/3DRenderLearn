//
// Created by 龚喜 on 2024/8/19.
//

#ifndef ASSIMPDEMO_NATIVE_ROAM_VIEW_H
#define ASSIMPDEMO_NATIVE_ROAM_VIEW_H


#include <jni/jni.hpp>

class RoamRenderer;

class NativeRoamView {
public:
    static constexpr auto Name() { return "com/gx/kotlin/scene/roam/NativeRoamView"; };

    static void registerNative(JNIEnv& env);

    NativeRoamView(jni::JNIEnv&, const jni::Object<NativeRoamView>&, const jni::Object<RoamRenderer>&);

    ~NativeRoamView();

private:
    void moveBy(jni::JNIEnv&, jni::jdouble, jni::jdouble, jni::jlong);

    void setBearingXY(jni::JNIEnv&, jni::jdouble, jni::jdouble, jni::jdouble, jni::jlong);

    void setPitch(jni::JNIEnv&, jni::jdouble, jni::jlong);

    void setZoom(jni::JNIEnv&, jni::jdouble, jni::jdouble, jni::jdouble, jni::jlong);

private:
    RoamRenderer& mRoamRenderer;

};


#endif //ASSIMPDEMO_NATIVE_ROAM_VIEW_H
