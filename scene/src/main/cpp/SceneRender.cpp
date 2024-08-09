#include <jni.h>
#include <string>
#include "RenderLogger.h"
#include "JNIHelper.h"
#include "AssimpModel.h"

AssimpModel *gAssimpObject = NULL;

JNIHelper *gHelperObject = NULL;


static jstring stringFromJNI(JNIEnv* env, jobject object) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}

static void OnDrawFrame(JNIEnv* env, jobject object) {
    LOGI("OnDrawFrame ENTER");
    if (gAssimpObject == NULL) {
        return;
    }
    gAssimpObject->Render();
}

static void OnSurfaceChanged(JNIEnv* env, jobject object, jint width, jint height) {
    LOGI("OnSurfaceChange width: %d, height: %d", width, height);
    if (gAssimpObject == NULL) {
        return;
    }
    gAssimpObject->SetViewport(width, height);
}

static void onSurfaceCreated(JNIEnv* env, jobject object) {
    LOGI("onSurfaceCreated enter");
    if (gAssimpObject == NULL) {
        return;
    }
    gAssimpObject->PerformGLInits();
}

static void OnModelCreated(JNIEnv* env, jobject object, jobject assetManager, jstring path) {
    LOGI("OnModelCreated");
    gHelperObject = new JNIHelper(env, object, assetManager, path);
    gAssimpObject = new AssimpModel();
}

static void OnModelDeleted(JNIEnv* env, jobject object) {
    LOGI("OnModelDeleted enter");
    if (gAssimpObject != NULL) {
        delete gAssimpObject;
    }
    gAssimpObject = NULL;

    if (gHelperObject != NULL) {
        delete gHelperObject;
    }
    gHelperObject = NULL;
}

static void OnSceneMove(JNIEnv* env, jobject object, jfloat distanceX, jfloat distanceY) {
    LOGI("OnSceneMove enter distanceX: %.2f  distanceY %.2f", distanceX, distanceY);
    if (gAssimpObject == NULL) {
        return;
    }

    float dX = distanceX / gAssimpObject->GetScreenWidth();
    float dY = -distanceY / gAssimpObject->GetScreenHeight();
    gAssimpObject->MoveAction(dX, dY);
}

static void OnSceneScroll(JNIEnv* env, jobject object, jfloat distanceX, jfloat distanceY, jfloat positionX, jfloat positionY) {
    LOGI("OnSceneScroll enter distanceX: %.2f, distanceY:%.2f, positionX:%.2f, positionY:%.2f", distanceX, distanceY, positionX, positionY);
    if (gAssimpObject == NULL) {
        return;
    }
    // normalize movements on the screen wrt GL surface dimensions
    // invert dY to be consistent with GLES conventions
    float dX = (float) distanceX / gAssimpObject->GetScreenWidth();
    float dY = -(float) distanceY / gAssimpObject->GetScreenHeight();
    float posX = 2*positionX/ gAssimpObject->GetScreenWidth() - 1.;
    float posY = -2*positionY / gAssimpObject->GetScreenHeight() + 1.;
    posX = fmax(-1., fmin(1., posX));
    posY = fmax(-1., fmin(1., posY));
    gAssimpObject->ScrollAction(dX, dY, posX, posY);
}

static void OnSceneScale(JNIEnv* env, jobject object, jfloat scaleFactor) {
    LOGI("OnSceneScale enter scaleFactor:.2f%", scaleFactor);
    if (gAssimpObject == NULL) {
        return;
    }
    gAssimpObject->ScaleAction((float) scaleFactor);
}

static void OnSceneDoubleTab(JNIEnv* env, jobject object) {
    LOGI("OnSceneDoubleTab enter");
    if (gAssimpObject == NULL) {
        return;
    }
    gAssimpObject->DoubleTapAction();
}

static JNINativeMethod methods[] = {
        {"stringFromJNI", "()Ljava/lang/String;", (void *)stringFromJNI},
        {"onDrawFrame",  "()V",  (void *)OnDrawFrame},
        {"onSurfaceChanged",  "(II)V",  (void *)OnSurfaceChanged},
        {"onSurfaceCreated",  "()V",  (void *)onSurfaceCreated},
        {"onModelCreated",  "(Landroid/content/res/AssetManager;Ljava/lang/String;)V",  (void *)OnModelCreated},
        {"onModelDeleted",  "()V",  (void *)OnModelDeleted},
        {"onSceneMove",  "(FF)V",  (void *)OnSceneMove},
        {"onSceneScroll",  "(FFFF)V",  (void *)OnSceneScroll},
        {"onSceneScale",  "(F)V",  (void *)OnSceneScale},
        {"onSceneDoubleTab",  "()V",  (void *)OnSceneDoubleTab}
};


static jint registerNativeMethods(JNIEnv *env, const char *className, JNINativeMethod *methods,
                                  int numMethods) {
    jclass clazz = env->FindClass(className);
    if (nullptr == clazz) {
        LOGE( "Find class %s failed! Is %s not exist? %s", className);
        return JNI_FALSE;
    }

    if (env->RegisterNatives(clazz, methods, numMethods) < 0) {
        LOGE( "RegisterNatives failed for %s", className);
        return JNI_FALSE;
    }
    return JNI_TRUE;
}


static jint registerNatives(JNIEnv *env, const char *className) {
    // 注册OSG 相关JNI调用函数
    if (!registerNativeMethods(env, className, methods,
                               sizeof(methods) / sizeof(methods[0]))) {
        return JNI_FALSE;
    }
    return JNI_TRUE;
}

extern "C"
JNIEXPORT jint JNI_OnLoad(JavaVM *vm, void *reserved) {
    JNIEnv *env = nullptr;
    jint result = JNI_ERR;
    LOGI( "JNI_OnLoad enter.");

    if (vm->GetEnv((void **) &env, JNI_VERSION_1_6) != JNI_OK) {
        LOGE( "ERROR: GetEnv failed");
        return result;
    }
    assert(env != nullptr);
    if (registerNatives(env, "com/gx/kotlin/scene/NativeRenderScene") == JNI_FALSE) {
        LOGE( "NativeRenderScene native registration failed");
        return result;
    }

    result = JNI_VERSION_1_6;

    return result;
}


extern "C"
JNIEXPORT void JNI_OnUnload(JavaVM *vm, void *reserved) {
    LOGI( "JNI_OnUnload enter.");
    JNIEnv *env;
    if (vm->GetEnv((void **) &env, JNI_VERSION_1_6) != JNI_OK) {
        LOGE( "ERROR: GetEnv failed");
        return;
    }
}