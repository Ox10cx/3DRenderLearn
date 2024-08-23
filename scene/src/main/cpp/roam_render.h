//
// Created by 龚喜 on 2024/8/18.
//

#ifndef ASSIMPDEMO_ROAM_RENDER_H
#define ASSIMPDEMO_ROAM_RENDER_H

#include <jni/jni.hpp>
#include "AssetManager.h"

class RoamRender {
public:
    static constexpr auto Name() { return "com/gx/kotlin/scene/roam/render/RoamRender"; };

    static void registerNative(JNIEnv& env);

    RoamRender(jni::JNIEnv& _env, const jni::Object<RoamRender>&, const jni::Object<AssetManager>& assetManager, const jni::String& path);

    ~RoamRender();


private:

    void onSurfaceCreated(JNIEnv&);

    void onSurfaceChanged(JNIEnv&, jint width, jint height);

    void onSurfaceDestroyed(JNIEnv&);

    void onRendererReset(JNIEnv&);

    void render(JNIEnv&);

};


#endif //ASSIMPDEMO_ROAM_RENDER_H
