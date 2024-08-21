package com.gx.kotlin.scene.roam.render;

import android.content.Context;
import android.content.res.AssetManager;

import androidx.annotation.NonNull;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

public abstract class RoamRender {

    static {
        System.loadLibrary("native-lib");
    }

    private long nativePtr = 0;

    public RoamRender(@NonNull Context context) {
        // Initialise native peer
        nativeInitialize(this, context.getAssets(), context.getFilesDir().getAbsolutePath());
    }

    public void onStart() {
        // Implement if needed
    }

    public void onPause() {
        // Implement if needed
    }

    public void onResume() {
        // Implement if needed
    }

    public void onStop() {
        // Implement if needed
    }

    public void onDestroy() {
        // Implement if needed
    }


    protected void onSurfaceCreated(GL10 gl, EGLConfig config) {
        nativeOnSurfaceCreated();
    }

    protected void onSurfaceChanged(@NonNull GL10 gl, int width, int height) {
        gl.glViewport(0, 0, width, height);
        nativeOnSurfaceChanged(width, height);
    }


    protected void onSurfaceDestroyed() {
        nativeOnSurfaceDestroyed();
    }

    protected void onDrawFrame(GL10 gl) {
        nativeRender();
    }

    private native void nativeInitialize(RoamRender self, AssetManager assetManager, String path);

    @Override
    protected native void finalize() throws Throwable;

    private native void nativeOnSurfaceCreated();

    private native void nativeOnSurfaceChanged(int width, int height);

    private native void nativeOnSurfaceDestroyed();

    protected native void nativeReset();

    private native void nativeRender();


}
