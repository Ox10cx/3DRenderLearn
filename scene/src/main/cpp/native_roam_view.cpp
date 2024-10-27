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
                                            METHOD(&NativeRoamView::setBearingXY, "nativeSetBearingXY"),
                                            METHOD(&NativeRoamView::setPitch, "nativeSetPitch"),
                                            METHOD(&NativeRoamView::setZoom, "nativeSetZoom"),
                                            METHOD(&NativeRoamView::getCameraPosition, "nativeGetCameraPosition"),
                                            METHOD(&NativeRoamView::jumpTo, "nativeJumpTo"));
}


void NativeRoamView::resizeView(jni::JNIEnv&, int w, int h) {
    mWidth = std::max(64, w);
    mHeight = std::max(64, h);
    LOGI("NativeRoamView resize [%d, %d]", w, h);
    mRoam->setSize({ static_cast<uint32_t>(mWidth), static_cast<uint32_t>(mHeight) });
}


void NativeRoamView::moveBy(jni::JNIEnv&, jni::jdouble dx, jni::jdouble dy, jni::jlong duration) {
    LOGI("NativeRoamView moveBy %.2f %.2f", dx, dy);
    mRoam->moveBy({dx, dy});
}

void NativeRoamView::setBearingXY(jni::JNIEnv&, jni::jdouble degrees, jni::jdouble cx, jni::jdouble cy, jni::jlong duration) {
    LOGI("NativeRoamView setBearingXY %.2f", degrees);
    roamgl::ScreenCoordinate anchor(cx, cy);
    mRoam->easeTo(roamgl::CameraOptions().withBearing(degrees).withAnchor(anchor));
}

void NativeRoamView::setPitch(jni::JNIEnv&, jni::jdouble pitch, jni::jlong duration) {
    LOGI("NativeRoamView setPitch %.2f ", pitch);
    mRoam->easeTo(roamgl::CameraOptions().withPitch(pitch));
}

void NativeRoamView::setZoom(jni::JNIEnv&, jni::jdouble zoom, jni::jdouble x, jni::jdouble y, jni::jlong duration) {
    LOGI("NativeRoamView setZoom %.2f ", zoom);
    mRoamRenderer.requestRender();
}

jni::Local<jni::Object<CameraPosition>> NativeRoamView::getCameraPosition(jni::JNIEnv& env)
{
    return CameraPosition::New(env, mRoam->getCameraOptions(insets));
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

