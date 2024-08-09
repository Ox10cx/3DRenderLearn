package com.gx.kotlin.scene.render;

import android.opengl.GLSurfaceView;

import com.gx.kotlin.scene.NativeRenderScene;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

public class SceneRender implements GLSurfaceView.Renderer {
    @Override
    public void onSurfaceCreated(GL10 gl10, EGLConfig eglConfig) {
        NativeRenderScene.onSurfaceCreated();
    }

    @Override
    public void onSurfaceChanged(GL10 gl10, int i, int i1) {
        NativeRenderScene.onSurfaceChanged(i, i1);
    }

    @Override
    public void onDrawFrame(GL10 gl10) {
        NativeRenderScene.onDrawFrame();
    }
}
