//
// Created by 龚喜 on 2024/8/18.
//

#ifndef ASSIMPDEMO_ROAM_RENDERER_H
#define ASSIMPDEMO_ROAM_RENDERER_H

#include <jni/jni.hpp>
#include <android/asset_manager.h>
#include "asset_manager.h"
#include "renderer/renderer.h"
#include "GLCamera.h"


class RoamRenderer {
public:
    static constexpr auto Name() { return "com/gx/kotlin/scene/roam/render/RoamRenderer"; };

    static void registerNative(JNIEnv& env);

    static RoamRenderer& getNativePeer(JNIEnv&, const jni::Object<RoamRenderer>&);

    RoamRenderer(jni::JNIEnv& _env, const jni::Object<RoamRenderer>&, const jni::Object<AssetManager>& assetManager, const jni::String& path);

    ~RoamRenderer();

    void update(std::shared_ptr<GLCamera>);

    void requestRender();

private:

    void onSurfaceCreated(JNIEnv&);

    void onSurfaceChanged(JNIEnv&, jint width, jint height);

    void onSurfaceDestroyed(JNIEnv&);

    void onRendererReset(JNIEnv&);

    void render(JNIEnv&);

private:
    jni::WeakReference<jni::Object<RoamRenderer>, jni::EnvAttachingDeleter> javaPeer;

    AAssetManager* mAssetManager;
    std::string mPath;

    std::shared_ptr<GLCamera> mCamera;
    std::mutex updateMutex;
    std::unique_ptr<Renderer> renderer;


};


#endif //ASSIMPDEMO_ROAM_RENDERER_H
