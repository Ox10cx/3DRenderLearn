package com.gx.kotlin.scene;

import android.content.res.AssetManager;

public class NativeRenderScene {

    static {
        System.loadLibrary("native-lib");
    }

    public static native String stringFromJNI();

    public static native void onDrawFrame();

    public static native void onSurfaceCreated();

    public static native void onSurfaceChanged(int width, int height);

    public static native void onModelCreated(AssetManager assetManager, String path);

    public static native void onModelDeleted();

    public static native void onSceneMove(float distanceX, float distanceY);

    public static native void onSceneScroll(float distanceX, float distanceY, float positionX, float positionY);

    public static native void onSceneScale(float scaleFactor);

    public static native void onSceneDoubleTab();
}
