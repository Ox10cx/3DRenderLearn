//
// Created by 龚喜 on 2024/8/19.
//

#include "native_roam_view.h"
#include "RenderLogger.h"
#include "roam_renderer.h"
#include "GLCamera.h"


NativeRoamView::NativeRoamView(jni::JNIEnv& _env,
                               const jni::Object<NativeRoamView>& obj,
                               const jni::Object<RoamRenderer>& jMapRender)
                               :mRoamRenderer(RoamRenderer::getNativePeer(_env, jMapRender))
{
    GLCamera camera;
    mRoamRenderer.update(std::make_shared<GLCamera>(std::move(camera)));
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
                                            jni::MakePeer<NativeRoamView, const jni::Object<NativeRoamView>&, const jni::Object<RoamRenderer>&>,
                                            "nativeInitialize", "nativeDestroy",
                                            METHOD(&NativeRoamView::moveBy, "nativeMoveBy"),
                                            METHOD(&NativeRoamView::setBearingXY, "nativeSetBearingXY"),
                                            METHOD(&NativeRoamView::setPitch, "nativeSetPitch"),
                                            METHOD(&NativeRoamView::setZoom, "nativeSetZoom"));
}

void NativeRoamView::moveBy(jni::JNIEnv&, jni::jdouble dx, jni::jdouble dy, jni::jlong duration) {
    LOGI("NativeRoamView moveBy %.2f %.2f ", dx, dy);
    mRoamRenderer.requestRender();
}

void NativeRoamView::setBearingXY(jni::JNIEnv&, jni::jdouble degrees, jni::jdouble cx, jni::jdouble cy, jni::jlong duration) {
    LOGI("NativeRoamView setBearingXY %.2f ", degrees);
    mRoamRenderer.requestRender();
}

void NativeRoamView::setPitch(jni::JNIEnv&, jni::jdouble pitch, jni::jlong duration) {
    LOGI("NativeRoamView setPitch %.2f ", pitch);
    mRoamRenderer.requestRender();
}

void NativeRoamView::setZoom(jni::JNIEnv&, jni::jdouble zoom, jni::jdouble x, jni::jdouble y, jni::jlong duration) {
    LOGI("NativeRoamView setZoom %.2f ", zoom);
    mRoamRenderer.requestRender();
}
