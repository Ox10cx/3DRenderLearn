package com.gx.kotlin.scene.view;

import android.content.Context;
import android.opengl.GLSurfaceView;
import android.util.AttributeSet;

import com.gx.kotlin.scene.render.SceneRender;

public class SceneRenderGLSurfaceView extends GLSurfaceView {
    public SceneRenderGLSurfaceView(Context context) {
        this(context, null);
    }

    public SceneRenderGLSurfaceView(Context context, AttributeSet attrs) {
        super(context, attrs);
        setEGLContextClientVersion(2);
        SceneRender render = new SceneRender();
        setRenderer(render);
        setRenderMode(GLSurfaceView.RENDERMODE_CONTINUOUSLY);
    }
}
