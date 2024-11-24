#include "way_point_bounds.h"

namespace android {

jni::Local<jni::Object<WayPointBounds>> WayPointBounds::New(jni::JNIEnv& env, roamgl::WayPointBounds bounds) {
    static auto& javaClass = jni::Class<WayPointBounds>::Singleton(env);
    static auto constructor = javaClass.GetConstructor<double, double, double, double>(env);
    return javaClass.New(env, constructor, bounds.north(), bounds.east(), bounds.south(), bounds.west());
}


roamgl::WayPointBounds WayPointBounds::getWayPointBounds(jni::JNIEnv& env, const jni::Object<WayPointBounds>& bounds) {
    static auto& javaClass = jni::Class<WayPointBounds>::Singleton(env);
    static auto swYField = javaClass.GetField<jni::jdouble>(env, "ySouth");
    static auto swXField = javaClass.GetField<jni::jdouble>(env, "xWest");
    static auto neYField = javaClass.GetField<jni::jdouble>(env, "yNorth");
    static auto neXField = javaClass.GetField<jni::jdouble>(env, "xEast");

    roamgl::WayPoint sw = {bounds.Get(env, swYField), bounds.Get(env, swXField) };
    roamgl::WayPoint ne = {bounds.Get(env, neYField), bounds.Get(env, neXField) };

    return roamgl::WayPointBounds::hull(sw, ne);
}

void WayPointBounds::registerNative(jni::JNIEnv& env) {
    jni::Class<WayPointBounds>::Singleton(env);
}

}


