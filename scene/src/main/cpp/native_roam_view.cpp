//
// Created by 龚喜 on 2024/8/19.
//

#include "native_roam_view.h"
#include "RenderLogger.h"
#include "roam_renderer.h"
#include "android_renderer_frontend.h"
#include "roam/roam_options.h"
#include "GLCamera.h"
#include <cmath>


NativeRoamView::NativeRoamView(jni::JNIEnv& _env,
                               const jni::Object<NativeRoamView>& obj,
                               const jni::Object<RoamRenderer>& jMapRender,
                               jni::jfloat _pixelRatio)
                               :mRoamRenderer(RoamRenderer::getNativePeer(_env, jMapRender))
                               ,mPixelRatio(_pixelRatio)
{
    mRendererFrontend = std::make_unique<AndroidRendererFrontend>(mRoamRenderer);

    roamgl::RoamOptions options;
    options.withSize(roamgl::Size{ static_cast<uint32_t>(mWidth), static_cast<uint32_t>(mHeight) })
    .withPixelRatio(mPixelRatio);

    mRoam = std::make_unique<roamgl::Roam>(*mRendererFrontend, options);

//    GLCamera camera;
//    mRoamRenderer.update(std::make_shared<GLCamera>(std::move(camera)));
}

NativeRoamView::~NativeRoamView()
{

}

void NativeRoamView::registerNative(JNIEnv& env) {
    // Lookup the class
    static auto& javaClass = jni::Class<NativeRoamView>::Singleton(env);


#define METHOD(MethodPtr, name) jni::MakeNativePeerMethod<decltype(MethodPtr), (MethodPtr)>(name)

    // Register the peer
    jni::RegisterNativePeer<NativeRoamView>(env, javaClass, "nativePtr",
                                            jni::MakePeer<NativeRoamView, const jni::Object<NativeRoamView>&, const jni::Object<RoamRenderer>&, jni::jfloat>,
                                            "nativeInitialize", "nativeDestroy",
                                            METHOD(&NativeRoamView::resizeView, "nativeResizeView"),
                                            METHOD(&NativeRoamView::moveBy, "nativeMoveBy"),
                                            METHOD(&NativeRoamView::easeTo, "nativeEaseTo"),
                                            METHOD(&NativeRoamView::setBearingXY, "nativeSetBearingXY"),
                                            METHOD(&NativeRoamView::getBearing, "nativeGetBearing"),
                                            METHOD(&NativeRoamView::setPitch, "nativeSetPitch"),
                                            METHOD(&NativeRoamView::getPitch, "nativeGetPitch"),
                                            METHOD(&NativeRoamView::getZoom, "nativeGetZoom"),
                                            METHOD(&NativeRoamView::setZoom, "nativeSetZoom"),
                                            METHOD(&NativeRoamView::setMinZoom, "nativeSetMinZoom"),
                                            METHOD(&NativeRoamView::getMinZoom, "nativeGetMinZoom"),
                                            METHOD(&NativeRoamView::setMaxZoom, "nativeSetMaxZoom"),
                                            METHOD(&NativeRoamView::getMaxZoom, "nativeGetMaxZoom"),
                                            METHOD(&NativeRoamView::getCameraPosition, "nativeGetCameraPosition"),
                                            METHOD(&NativeRoamView::jumpTo, "nativeJumpTo"),
                                            METHOD(&NativeRoamView::setWayPoint, "nativeSetWayPoint"),
                                            METHOD(&NativeRoamView::setWayPointBounds, "nativeSetWayPointBounds"),
                                            METHOD(&NativeRoamView::getCameraForWayPointBounds, "nativeGetCameraForWayPointBounds"),
                                            METHOD(&NativeRoamView::pixelForWayPoint, "nativePixelForWayPoint"),
                                            METHOD(&NativeRoamView::wayPointForPixel, "nativeWayPointForPixel")
                                            );
}


void NativeRoamView::resizeView(jni::JNIEnv&, int w, int h) {
    mWidth = std::max(64, w);
    mHeight = std::max(64, h);
    mRoam->setSize({ static_cast<uint32_t>(mWidth), static_cast<uint32_t>(mHeight) });
}


void NativeRoamView::moveBy(jni::JNIEnv&, jni::jdouble dx, jni::jdouble dy, jni::jlong duration) {
    LOGI("NativeRoamView moveBy %.2f %.2f", dx, dy);
    mRoam->moveBy({dx, dy});
}

void NativeRoamView::easeTo(jni::JNIEnv&, jni::jdouble bearing, jni::jdouble x, jni::jdouble y, jni::jlong duration, jni::jdouble pitch, jni::jdouble zoom, jni::jboolean easing) {
    roamgl::CameraOptions cameraOptions;
    if (bearing != -1) {
        cameraOptions.bearing = bearing;
    }
    cameraOptions.center = roamgl::WayPoint(x, y);
    cameraOptions.padding = insets;
    if (pitch != -1) {
        cameraOptions.pitch = pitch;
    }
    if (zoom != -1) {
        cameraOptions.zoom = zoom;
    }

    roamgl::AnimationOptions animationOptions;
    animationOptions.duration.emplace(roamgl::Milliseconds(duration));
    if (!easing) {
        // add a linear interpolator instead of easing
        animationOptions.easing.emplace(roamgl::util::UnitBezier { 0, 0, 1, 1 });
    }

    mRoam->easeTo(cameraOptions, animationOptions);
}

void NativeRoamView::setBearingXY(jni::JNIEnv&, jni::jdouble degrees, jni::jdouble cx, jni::jdouble cy, jni::jlong duration) {
    LOGI("NativeRoamView setBearingXY %.2f", degrees);
    roamgl::ScreenCoordinate anchor(cx, cy);
    mRoam->easeTo(roamgl::CameraOptions().withBearing(degrees).withAnchor(anchor), roamgl::AnimationOptions{roamgl::Milliseconds(duration)});
}

jni::jdouble NativeRoamView::getBearing(jni::JNIEnv&) {
    return *mRoam->getCameraOptions().bearing;
}

jni::jdouble NativeRoamView::getPitch(jni::JNIEnv&) {
    return *mRoam->getCameraOptions().pitch;
}

void NativeRoamView::setPitch(jni::JNIEnv&, jni::jdouble pitch, jni::jlong duration) {
    LOGI("NativeRoamView setPitch %.2f ", pitch);
    mRoam->easeTo(roamgl::CameraOptions().withPitch(pitch), roamgl::AnimationOptions{roamgl::Milliseconds(duration)});
}

void NativeRoamView::setZoom(jni::JNIEnv&, jni::jdouble zoom, jni::jdouble x, jni::jdouble y, jni::jlong duration) {
    LOGI("NativeRoamView setZoom %.2f [%.2f, %.2f]", zoom, x, y);
    mRoam->easeTo(roamgl::CameraOptions().withZoom(zoom).withAnchor(roamgl::ScreenCoordinate{ x, y }), roamgl::AnimationOptions{roamgl::Milliseconds(duration)});
}

jni::jdouble NativeRoamView::getZoom(jni::JNIEnv&) {
    return *(mRoam->getCameraOptions().zoom);
}

void NativeRoamView::setMinZoom(jni::JNIEnv&, jni::jdouble zoom)
{
    mRoam->setBounds(roamgl::BoundOptions().withMinZoom(zoom));
}

jni::jdouble NativeRoamView::getMinZoom(jni::JNIEnv&)
{
    return *mRoam->getBounds().minZoom;
}

void NativeRoamView::setMaxZoom(jni::JNIEnv&, jni::jdouble zoom)
{
    mRoam->setBounds(roamgl::BoundOptions().withMaxZoom(zoom));
}

jni::jdouble NativeRoamView::getMaxZoom(jni::JNIEnv&)
{
    return *mRoam->getBounds().maxZoom;
}

jni::Local<jni::Object<android::CameraPosition>> NativeRoamView::getCameraPosition(jni::JNIEnv& env)
{
    return android::CameraPosition::New(env, mRoam->getCameraOptions(insets));
}

void NativeRoamView::jumpTo(jni::JNIEnv&, jni::jdouble bearing, jni::jdouble wayPointX, jni::jdouble wayPointY, jni::jdouble pitch, jni::jdouble zoom)
{
    roamgl::CameraOptions options;
    if (bearing != -1) {
        options.bearing = bearing;
    }
    options.center = roamgl::WayPoint(wayPointX, wayPointY);
    if (pitch != -1) {
        options.pitch = pitch;
    }
    if (zoom != -1) {
        options.zoom = zoom;
    }

//    map->jumpTo(options);

}

void NativeRoamView::setWayPoint(jni::JNIEnv&, jni::jdouble wayPointX, jni::jdouble wayPointY, jni::jlong duration) {
    LOGI("setWayPoint setWayPoint %.2f %.2f ", wayPointX, wayPointY);
    mRoam->easeTo(roamgl::CameraOptions().withCenter(roamgl::WayPoint(wayPointX, wayPointY)).withPadding(insets), roamgl::AnimationOptions{roamgl::Milliseconds(duration)});
}

void NativeRoamView::setWayPointBounds(jni::JNIEnv& env, const jni::Object<android::WayPointBounds>& jBounds) {
    roamgl::BoundOptions bounds;
    if (jBounds) {
        bounds.withWayPointBounds(android::WayPointBounds::getWayPointBounds(env, jBounds));
    } else {
        bounds.withWayPointBounds(roamgl::WayPointBounds::unbounded());
    }
    mRoam->setBounds(bounds);
}

jni::Local<jni::Object<android::CameraPosition>> NativeRoamView::getCameraForWayPointBounds(jni::JNIEnv& env, const jni::Object<android::WayPointBounds>& jBounds, double top, double left, double bottom, double right, double bearing, double tilt) {
    roamgl::EdgeInsets padding = {top, left, bottom, right};
    return android::CameraPosition::New(env, mRoam->cameraForWayPointBounds(android::WayPointBounds::getWayPointBounds(env, jBounds), padding, bearing, tilt));
}


jni::Local<jni::Object<android::PointF>> NativeRoamView::pixelForWayPoint(JNIEnv& env, jdouble x, jdouble y)
{
    roamgl::ScreenCoordinate pixel = mRoam->pixelForWayPoint(roamgl::WayPoint(x, y));
    return android::PointF::New(env, static_cast<float>(pixel.x), static_cast<float>(pixel.y));
}


jni::Local<jni::Object<android::WayPoint>> NativeRoamView::wayPointForPixel(JNIEnv& env, jfloat x, jfloat y)
{
    return android::WayPoint::New(env, mRoam->wayPointForPixel(roamgl::ScreenCoordinate(x, y)));
}
