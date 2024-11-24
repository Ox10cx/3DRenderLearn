#pragma once

#include "utils/geo.h"
#include "utils/geometry.h"
#include <jni/jni.hpp>

namespace android {

class WayPointBounds {
public:

    static constexpr auto Name() { return "com/gx/kotlin/scene/geometry/WayPointBounds"; };

    static jni::Local<jni::Object<WayPointBounds>> New(jni::JNIEnv&, roamgl::WayPointBounds);

    static roamgl::WayPointBounds getWayPointBounds(jni::JNIEnv&, const jni::Object<WayPointBounds>&);

    static void registerNative(jni::JNIEnv&);
};

}





