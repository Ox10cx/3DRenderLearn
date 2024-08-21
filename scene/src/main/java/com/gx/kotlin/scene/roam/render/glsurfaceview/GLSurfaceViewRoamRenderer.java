package com.gx.kotlin.scene.roam.render.glsurfaceview;

import static android.opengl.GLSurfaceView.RENDERMODE_WHEN_DIRTY;

import android.content.Context;
import android.opengl.GLSurfaceView;

import androidx.annotation.NonNull;

import com.gx.kotlin.scene.roam.render.RoamRender;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

public class GLSurfaceViewRoamRenderer extends RoamRender implements GLSurfaceView.Renderer {
    @NonNull
    private final RoamGLSurfaceView glSurfaceView;

    public GLSurfaceViewRoamRenderer(Context context,
                                     RoamGLSurfaceView glSurfaceView) {
        super(context);
        this.glSurfaceView = glSurfaceView;
        glSurfaceView.setEGLContextClientVersion(2);
        glSurfaceView.setRenderer(this);
        glSurfaceView.setRenderMode(RENDERMODE_WHEN_DIRTY);
        glSurfaceView.setPreserveEGLContextOnPause(true);
        glSurfaceView.setDetachedListener(new RoamGLSurfaceView.OnGLSurfaceViewDetachedListener() {
            @Override
            public void onGLSurfaceViewDetached() {
                nativeReset();
            }
        });
    }

    @Override
    public void onStop() {
        glSurfaceView.onPause();
    }

    @Override
    public void onPause() {
        super.onPause();
    }

    @Override
    public void onDestroy() {
        super.onDestroy();
    }

    @Override
    public void onStart() {
        glSurfaceView.onResume();
    }

    @Override
    public void onResume() {
        super.onResume();
    }


    @Override
    public void onSurfaceCreated(GL10 gl10, EGLConfig eglConfig) {
        super.onSurfaceCreated(gl10, eglConfig);
    }

    @Override
    protected void onSurfaceDestroyed() {
        super.onSurfaceDestroyed();
    }

    @Override
    public void onSurfaceChanged(GL10 gl10, int width, int height) {
        super.onSurfaceChanged(gl10, width, height);
    }

    @Override
    public void onDrawFrame(GL10 gl10) {
        super.onDrawFrame(gl10);
    }
}
