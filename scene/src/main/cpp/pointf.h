//
// Created by gongxi on 2024/11/24.
//

#ifndef ASSIMPDEMO_POINTF_H
#define ASSIMPDEMO_POINTF_H

#include <jni/jni.hpp>
#include "utils/geo.h"

namespace android {

class PointF{
public:

    static constexpr auto Name() { return "android/graphics/PointF"; };

    static jni::Local<jni::Object<PointF>> New(jni::JNIEnv&, float, float);

    static roamgl::ScreenCoordinate getScreenCoordinate(jni::JNIEnv&, const jni::Object<PointF>&);

    static void registerNative(jni::JNIEnv&);
};


}


#endif //ASSIMPDEMO_POINTF_H
