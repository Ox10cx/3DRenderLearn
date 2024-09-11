//
// Created by 龚喜 on 2024/8/19.
//

#ifndef ASSIMPDEMO_NATIVE_ROAM_VIEW_H
#define ASSIMPDEMO_NATIVE_ROAM_VIEW_H


#include <jni/jni.hpp>
#include <roam/roam.h>
#include <memory>

#include "camera_position.h"

class AndroidRendererFrontend;
class RoamRenderer;

class NativeRoamView {
public:
    static constexpr auto Name() { return "com/gx/kotlin/scene/roam/NativeRoamView"; };

    static void registerNative(JNIEnv& env);

    NativeRoamView(jni::JNIEnv&, const jni::Object<NativeRoamView>&, const jni::Object<RoamRenderer>&, jni::jfloat);

    ~NativeRoamView();

private:

    void resizeView(jni::JNIEnv&, int, int);

    void moveBy(jni::JNIEnv&, jni::jdouble, jni::jdouble, jni::jlong);

    void setBearingXY(jni::JNIEnv&, jni::jdouble, jni::jdouble, jni::jdouble, jni::jlong);

    void setPitch(jni::JNIEnv&, jni::jdouble, jni::jlong);

    void setZoom(jni::JNIEnv&, jni::jdouble, jni::jdouble, jni::jdouble, jni::jlong);

    jni::Local<jni::Object<CameraPosition>> getCameraPosition(jni::JNIEnv&);

    void jumpTo(jni::JNIEnv&, jni::jdouble bearing, jni::jdouble wayPointX, jni::jdouble wayPointY, jni::jdouble pitch, jni::jdouble zoom);


private:
    std::unique_ptr<AndroidRendererFrontend> mRendererFrontend;
    RoamRenderer& mRoamRenderer;

    float mPixelRatio;

    int mWidth = 64;
    int mHeight = 64;
    std::unique_ptr<roamgl::Roam> mRoam;
    roamgl::EdgeInsets insets;

};


#endif //ASSIMPDEMO_NATIVE_ROAM_VIEW_H
