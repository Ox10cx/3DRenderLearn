//
// Created by 龚喜 on 2024/8/19.
//

#ifndef ASSIMPDEMO_NATIVE_ROAM_VIEW_H
#define ASSIMPDEMO_NATIVE_ROAM_VIEW_H


#include <jni/jni.hpp>
#include <roam/roam.h>
#include <memory>

#include "camera_position.h"
#include "pointf.h"
#include "way_point.h"
#include "way_point_bounds.h"


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

    void easeTo(jni::JNIEnv&, jni::jdouble, jni::jdouble, jni::jdouble, jni::jlong, jni::jdouble, jni::jdouble, jni::jboolean);

    void setBearingXY(jni::JNIEnv&, jni::jdouble, jni::jdouble, jni::jdouble, jni::jlong);

    jni::jdouble getBearing(jni::JNIEnv&);

    void setPitch(jni::JNIEnv&, jni::jdouble, jni::jlong);

    jni::jdouble getPitch(jni::JNIEnv&);

    void setZoom(jni::JNIEnv&, jni::jdouble, jni::jdouble, jni::jdouble, jni::jlong);

    jni::jdouble getZoom(jni::JNIEnv&);

    void setMinZoom(jni::JNIEnv&, jni::jdouble);

    jni::jdouble getMinZoom(jni::JNIEnv&);

    void setMaxZoom(jni::JNIEnv&, jni::jdouble);

    jni::jdouble getMaxZoom(jni::JNIEnv&);

    jni::Local<jni::Object<android::CameraPosition>> getCameraPosition(jni::JNIEnv&);

    void jumpTo(jni::JNIEnv&, jni::jdouble bearing, jni::jdouble wayPointX, jni::jdouble wayPointY, jni::jdouble pitch, jni::jdouble zoom);

    void setWayPoint(jni::JNIEnv&, jni::jdouble, jni::jdouble, jni::jlong);

    void setWayPointBounds(jni::JNIEnv&, const jni::Object<android::WayPointBounds>&);

    jni::Local<jni::Object<android::CameraPosition>> getCameraForWayPointBounds(jni::JNIEnv&, const jni::Object<android::WayPointBounds>&, double top, double left, double bottom, double right, double bearing, double tilt);

    jni::Local<jni::Object<android::PointF>> pixelForWayPoint(JNIEnv&, jdouble, jdouble);

    jni::Local<jni::Object<android::WayPoint>> wayPointForPixel(JNIEnv&, jfloat, jfloat);


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
