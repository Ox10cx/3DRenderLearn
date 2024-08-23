//
// Created by 龚喜 on 2024/8/18.
//

#include "roam_render.h"
#include "JNIHelper.h"
#include "AssimpModel.h"
#include "roamgl/utils/log.h"


JNIHelper *gHelperObject = NULL;
AssimpModel *gAssimpObject = NULL;


RoamRender::RoamRender(jni::JNIEnv& _env,
                       const jni::Object<RoamRender>& obj,
                       const jni::Object<AssetManager>& assetManager,
                       const jni::String& path)
{

    gHelperObject = new JNIHelper(&_env, jni::Unwrap(assetManager.get()), jni::Make<std::string>(_env, path));
    gAssimpObject = new AssimpModel();
    Log::Info(Event::Render, " RoamRender initialize %s", jni::Make<std::string>(_env, path).c_str());
}

RoamRender::~RoamRender()
{

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


void RoamRender::onSurfaceCreated(JNIEnv& env)
{
    Log::Info(Event::Render, "onSurfaceCreated enter");
    if (gAssimpObject == NULL) {
        return;
    }
    gAssimpObject->PerformGLInits();
}

void RoamRender::onRendererReset(JNIEnv& env)
{

}

void RoamRender::onSurfaceChanged(JNIEnv&, jint width, jint height)
{
    Log::Info(Event::Render, "OnSurfaceChange width: %d, height: %d", width, height);
    if (gAssimpObject == NULL) {
        return;
    }
    gAssimpObject->SetViewport(width, height);
}

void RoamRender::onSurfaceDestroyed(JNIEnv&) {

}

void RoamRender::render(JNIEnv& env)
{
    Log::Info(Event::Render, " OnDrawFrame ENTER");
    if (gAssimpObject == NULL) {
        return;
    }
    gAssimpObject->Render();
}


