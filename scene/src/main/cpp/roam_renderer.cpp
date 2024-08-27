//
// Created by 龚喜 on 2024/8/18.
//

#include "roam_renderer.h"
#include "roamgl/utils/log.h"
#include <android/asset_manager_jni.h>
#include "attach_env.h"



RoamRenderer::RoamRenderer(jni::JNIEnv& _env,
                           const jni::Object<RoamRenderer>& obj,
                           const jni::Object<AssetManager>& assetManager,
                           const jni::String& path)
        : javaPeer(_env, obj)
{
    Log::Info(Event::Render, " RoamRenderer initialize %s", jni::Make<std::string>(_env, path).c_str());
    mAssetManager = AAssetManager_fromJava(&_env, jni::Unwrap(assetManager.get()));
    mPath = jni::Make<std::string>(_env, path);

}

RoamRenderer::~RoamRenderer()
{

}


void RoamRenderer::onSurfaceCreated(JNIEnv& env)
{
    Log::Info(Event::Render, "onSurfaceCreated enter");
    renderer.reset();
    renderer = std::make_unique<Renderer>(mAssetManager, mPath);
}

void RoamRenderer::onRendererReset(JNIEnv& env)
{

}

void RoamRenderer::onSurfaceChanged(JNIEnv&, jint width, jint height)
{
    Log::Info(Event::Render, "OnSurfaceChange width: %d, height: %d", width, height);
}

void RoamRenderer::onSurfaceDestroyed(JNIEnv&) {

}

void RoamRenderer::update(std::shared_ptr<GLCamera> camera) {
    // Lock on the parameters
    std::lock_guard<std::mutex> lock(updateMutex);
    mCamera = std::move(camera);
};


void RoamRenderer::render(JNIEnv& env)
{
    assert (renderer);
    std::shared_ptr<GLCamera> params;
    {
        // Lock on the parameters
        std::unique_lock<std::mutex> lock(updateMutex);
        if (!mCamera) return;

        // Hold on to the update parameters during render
        params = mCamera;
    }

    renderer->render();

    // todo 这里可以考虑相机参数传过来
}

void RoamRenderer::registerNative(JNIEnv& env) {
    // Lookup the class
    static auto& javaClass = jni::Class<RoamRenderer>::Singleton(env);


#define METHOD(MethodPtr, name) jni::MakeNativePeerMethod<decltype(MethodPtr), (MethodPtr)>(name)


    // Register the peer
    jni::RegisterNativePeer<RoamRenderer>(env, javaClass, "nativePtr",
                                          jni::MakePeer<RoamRenderer, const jni::Object<RoamRenderer>&, const jni::Object<AssetManager>&, const jni::String&>,
                                          "nativeInitialize", "finalize",
                                          METHOD(&RoamRenderer::render, "nativeRender"),
                                          METHOD(&RoamRenderer::onRendererReset, "nativeReset"),
                                          METHOD(&RoamRenderer::onSurfaceCreated,
                                               "nativeOnSurfaceCreated"),
                                          METHOD(&RoamRenderer::onSurfaceChanged,
                                               "nativeOnSurfaceChanged"),
                                          METHOD(&RoamRenderer::onSurfaceDestroyed,
                                               "nativeOnSurfaceDestroyed"));
}

RoamRenderer& RoamRenderer::getNativePeer(JNIEnv& env, const jni::Object<RoamRenderer>& jObject) {
    static auto& javaClass = jni::Class<RoamRenderer>::Singleton(env);
    static auto field = javaClass.GetField<jlong>(env, "nativePtr");
    RoamRenderer* roamRenderer = reinterpret_cast<RoamRenderer*>(jObject.Get(env, field));
    assert(roamRenderer != nullptr);
    return *roamRenderer;
}

void RoamRenderer::requestRender() {
    android::UniqueEnv _env = android::AttachEnv();
    static auto& javaClass = jni::Class<RoamRenderer>::Singleton(*_env);
    static auto onInvalidate = javaClass.GetMethod<void()>(*_env, "requestRender");
    auto weakReference = javaPeer.get(*_env);
    if (weakReference) {
        weakReference.Call(*_env, onInvalidate);
    }
}


