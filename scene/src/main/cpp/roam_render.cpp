//
// Created by 龚喜 on 2024/8/18.
//

#include "roam_render.h"
#include "roamgl/utils/log.h"
#include <android/asset_manager_jni.h>



RoamRender::RoamRender(jni::JNIEnv& _env,
                       const jni::Object<RoamRender>& obj,
                       const jni::Object<AssetManager>& assetManager,
                       const jni::String& path)
{
    Log::Info(Event::Render, " RoamRender initialize %s", jni::Make<std::string>(_env, path).c_str());
    mAssetManager = AAssetManager_fromJava(&_env, jni::Unwrap(assetManager.get()));
    mPath = jni::Make<std::string>(_env, path);

}

RoamRender::~RoamRender()
{

}


void RoamRender::onSurfaceCreated(JNIEnv& env)
{
    Log::Info(Event::Render, "onSurfaceCreated enter");
    renderer.reset();
    renderer = std::make_unique<Renderer>(mAssetManager, mPath);
}

void RoamRender::onRendererReset(JNIEnv& env)
{

}

void RoamRender::onSurfaceChanged(JNIEnv&, jint width, jint height)
{
    Log::Info(Event::Render, "OnSurfaceChange width: %d, height: %d", width, height);
}

void RoamRender::onSurfaceDestroyed(JNIEnv&) {

}

void RoamRender::update(std::shared_ptr<GLCamera> camera) {
    // Lock on the parameters
    std::lock_guard<std::mutex> lock(updateMutex);
    mCamera = std::move(camera);
};


void RoamRender::render(JNIEnv& env)
{
    Log::Info(Event::Render, " OnDrawFrame ENTER");

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

void RoamRender::registerNative(JNIEnv& env) {
    // Lookup the class
    static auto& javaClass = jni::Class<RoamRender>::Singleton(env);


#define METHOD(MethodPtr, name) jni::MakeNativePeerMethod<decltype(MethodPtr), (MethodPtr)>(name)


    // Register the peer
    jni::RegisterNativePeer<RoamRender>(env, javaClass, "nativePtr",
                                        jni::MakePeer<RoamRender, const jni::Object<RoamRender>&, const jni::Object<AssetManager>&, const jni::String&>,
                                        "nativeInitialize", "finalize",
                                        METHOD(&RoamRender::render, "nativeRender"),
                                        METHOD(&RoamRender::onRendererReset, "nativeReset"),
                                        METHOD(&RoamRender::onSurfaceCreated,
                                               "nativeOnSurfaceCreated"),
                                        METHOD(&RoamRender::onSurfaceChanged,
                                               "nativeOnSurfaceChanged"),
                                        METHOD(&RoamRender::onSurfaceDestroyed,
                                               "nativeOnSurfaceDestroyed"));
}

RoamRender& RoamRender::getNativePeer(JNIEnv& env, const jni::Object<RoamRender>& jObject) {
    static auto& javaClass = jni::Class<RoamRender>::Singleton(env);
    static auto field = javaClass.GetField<jlong>(env, "nativePtr");
    RoamRender* roamRenderer = reinterpret_cast<RoamRender*>(jObject.Get(env, field));
    assert(roamRenderer != nullptr);
    return *roamRenderer;
}


