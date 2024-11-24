//
// Created by gongxi on 2024/9/5.
//

#ifndef ASSIMPDEMO_WAY_POINT_H
#define ASSIMPDEMO_WAY_POINT_H

#include <jni/jni.hpp>
#include "geometry.h"
#include "utils/geo.h"

namespace android {

class WayPoint {
public:

    static constexpr auto Name() { return "com/gx/kotlin/scene/geometry/WayPoint"; };

    static jni::Local<jni::Object<WayPoint>> New(jni::JNIEnv&, const roamgl::WayPoint&);

    static roamgl::Point<double> getGeometry(jni::JNIEnv&, const jni::Object<WayPoint>&);

    static roamgl::WayPoint getWayPoint(jni::JNIEnv& env, const jni::Object<WayPoint>& wayPoint);

    static void registerNative(jni::JNIEnv&);
};

}

#endif //ASSIMPDEMO_WAY_POINT_H
