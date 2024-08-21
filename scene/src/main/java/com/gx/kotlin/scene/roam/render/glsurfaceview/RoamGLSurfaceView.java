package com.gx.kotlin.scene.roam.render.glsurfaceview;

import android.content.Context;
import android.opengl.GLSurfaceView;
import android.util.AttributeSet;

import androidx.annotation.NonNull;

public class RoamGLSurfaceView extends GLSurfaceView {

    private OnGLSurfaceViewDetachedListener detachedListener;

    public RoamGLSurfaceView(Context context) {
        super(context);
    }

    public RoamGLSurfaceView(Context context, AttributeSet attrs) {
        super(context, attrs);
    }

    @Override
    protected void onDetachedFromWindow() {
        if (detachedListener != null) {
            detachedListener.onGLSurfaceViewDetached();
        }
        super.onDetachedFromWindow();
    }

    /**
     * Set a listener that gets notified when the view is detached from window.
     *
     * @param detachedListener listener
     */
    public void setDetachedListener(@NonNull OnGLSurfaceViewDetachedListener detachedListener) {
        if (this.detachedListener != null) {
            throw new IllegalArgumentException("Detached from window listener has been already set.");
        }
        this.detachedListener = detachedListener;
    }


    public interface OnGLSurfaceViewDetachedListener {

        void onGLSurfaceViewDetached();
    }
}
