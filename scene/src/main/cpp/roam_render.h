//
// Created by 龚喜 on 2024/8/18.
//

#ifndef ASSIMPDEMO_ROAM_RENDER_H
#define ASSIMPDEMO_ROAM_RENDER_H

#include <jni/jni.hpp>
#include <android/asset_manager.h>
#include "asset_manager.h"
#include "renderer.h"
#include "GLCamera.h"


class RoamRender {
public:
    static constexpr auto Name() { return "com/gx/kotlin/scene/roam/render/RoamRender"; };

    static void registerNative(JNIEnv& env);

    static RoamRender& getNativePeer(JNIEnv&, const jni::Object<RoamRender>&);

    RoamRender(jni::JNIEnv& _env, const jni::Object<RoamRender>&, const jni::Object<AssetManager>& assetManager, const jni::String& path);

    ~RoamRender();

    void update(std::shared_ptr<GLCamera>);

private:

    void onSurfaceCreated(JNIEnv&);

    void onSurfaceChanged(JNIEnv&, jint width, jint height);

    void onSurfaceDestroyed(JNIEnv&);

    void onRendererReset(JNIEnv&);

    void render(JNIEnv&);

private:
    AAssetManager* mAssetManager;
    std::string mPath;

    std::shared_ptr<GLCamera> mCamera;
    std::mutex updateMutex;
    std::unique_ptr<Renderer> renderer;


};


#endif //ASSIMPDEMO_ROAM_RENDER_H
