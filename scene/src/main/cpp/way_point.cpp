//
// Created by gongxi on 2024/9/5.
//

#include "way_point.h"

jni::Local<jni::Object<WayPoint>> WayPoint::New(jni::JNIEnv& env, const roamgl::WayPoint& wayPoint) {
    static auto& javaClass = jni::Class<WayPoint>::Singleton(env);
    static auto constructor = javaClass.GetConstructor<double, double>(env);
    return javaClass.New(env, constructor, wayPoint.getY(), wayPoint.getY());
}

roamgl::Point<double> WayPoint::getGeometry(jni::JNIEnv& env, const jni::Object<WayPoint>& wayPoint) {
    static auto& javaClass = jni::Class<WayPoint>::Singleton(env);
    static auto xField = javaClass.GetField<jni::jdouble>(env, "x");
    static auto yField = javaClass.GetField<jni::jdouble>(env, "y");
    return roamgl::Point<double>(wayPoint.Get(env, xField), wayPoint.Get(env, yField));
}

roamgl::WayPoint WayPoint::getWayPoint(jni::JNIEnv& env, const jni::Object<WayPoint>& wayPoint) {
    auto point = WayPoint::getGeometry(env, wayPoint);
    return roamgl::WayPoint(point.y, point.x);
}

void WayPoint::registerNative(jni::JNIEnv& env) {
    jni::Class<WayPoint>::Singleton(env);
}
