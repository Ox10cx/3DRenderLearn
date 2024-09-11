//
// Created by gongxi on 2024/9/5.
//

#ifndef ASSIMPDEMO_CAMERA_POSITION_H
#define ASSIMPDEMO_CAMERA_POSITION_H

#include <roam/camera.h>
#include <jni/jni.hpp>


class CameraPosition {
public:
    static constexpr auto Name() { return "com/gx/kotlin/scene/camera/CameraPosition"; };

    static jni::Local<jni::Object<CameraPosition>> New(jni::JNIEnv&, roamgl::CameraOptions);

    static roamgl::CameraOptions getCameraOptions(jni::JNIEnv&, const jni::Object<CameraPosition>&);

    static void registerNative(jni::JNIEnv&);
};



#endif //ASSIMPDEMO_CAMERA_POSITION_H
