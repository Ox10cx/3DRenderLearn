//
// Created by gongxi on 2024/9/5.
//

#include "camera_position.h"
#include "way_point.h"

namespace android {

    jni::Local<jni::Object<CameraPosition>> CameraPosition::New(jni::JNIEnv &env, roamgl::CameraOptions options) {
        static auto& javaClass = jni::Class<CameraPosition>::Singleton(env);
        static auto constructor = javaClass.GetConstructor<jni::Object<WayPoint>, double, double, double>(env);

        // wrap LatLng values coming from core
        auto center = options.center.value();

        // convert bearing, measured in radians counterclockwise from true north.
        // Wrapped to [−π rad, π rad). Android binding from 0 to 360 degrees
        double bearing_degrees = options.bearing.value_or(0);
        while (bearing_degrees > 360) {
            bearing_degrees -= 360;
        }
        while (bearing_degrees < 0) {
            bearing_degrees += 360;
        }

        // convert tilt, core ranges from  [0 rad, 1,0472 rad], android ranges from 0 to 60
        double tilt_degrees = options.pitch.value_or(0);

        return javaClass.New(env, constructor, WayPoint::New(env, center), options.zoom.value_or(0), tilt_degrees, bearing_degrees);
    }

    roamgl::CameraOptions CameraPosition::getCameraOptions(jni::JNIEnv& env, const jni::Object<CameraPosition>& position) {
        static auto& javaClass = jni::Class<CameraPosition>::Singleton(env);
        static auto bearing = javaClass.GetField<jni::jdouble>(env, "bearing");
        static auto target = javaClass.GetField<jni::Object<WayPoint>>(env, "target");
        static auto tilt = javaClass.GetField<jni::jdouble>(env, "tilt");
        static auto zoom = javaClass.GetField<jni::jdouble>(env, "zoom");

        auto center = WayPoint::getWayPoint(env, position.Get(env, target));

        return roamgl::CameraOptions {
                center,
                {},
                {},
                position.Get(env, zoom),
                position.Get(env, bearing),
                position.Get(env, tilt)
        };
    }

    void CameraPosition::registerNative(jni::JNIEnv &env) {
        jni::Class<CameraPosition>::Singleton(env);
    }

}