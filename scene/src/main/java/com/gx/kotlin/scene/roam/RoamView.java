package com.gx.kotlin.scene.roam;

import android.content.Context;
import android.util.AttributeSet;
import android.util.Log;
import android.view.MotionEvent;
import android.widget.FrameLayout;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;

import com.gx.kotlin.scene.roam.render.RoamRender;
import com.gx.kotlin.scene.roam.render.glsurfaceview.GLSurfaceViewRoamRenderer;
import com.gx.kotlin.scene.roam.render.glsurfaceview.RoamGLSurfaceView;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

public class RoamView extends FrameLayout {
    private RoamRender mRoamRenderer;
    private NativeRoam mNativeRoamView;
    private RoamGestureDetector mRoamGestureDetector;

    public RoamView(@NonNull Context context) {
        super(context);
        initialize(context);
    }

    public RoamView(@NonNull Context context, @Nullable AttributeSet attrs) {
        super(context, attrs);
        initialize(context);
    }

    public RoamView(@NonNull Context context, @Nullable AttributeSet attrs, int defStyleAttr) {
        super(context, attrs, defStyleAttr);
        initialize(context);
    }

    protected void initialize(@NonNull final Context context) {
        initialiseDrawingSurface();
    }

    private void initialiseDrawingSurface() {
        RoamGLSurfaceView glSurfaceView = new RoamGLSurfaceView(getContext());
        glSurfaceView.setZOrderMediaOverlay(false);
        mRoamRenderer = new GLSurfaceViewRoamRenderer(getContext(), glSurfaceView) {
            @Override
            public void onSurfaceCreated(GL10 gl, EGLConfig config) {
                RoamView.this.onSurfaceCreated();
                super.onSurfaceCreated(gl, config);
            }
        };
        addView(glSurfaceView, 0);

        mNativeRoamView = new NativeRoamView(getContext(), mRoamRenderer);
    }

    private void onSurfaceCreated() {
        post(new Runnable() {
            @Override
            public void run() {
                RoamView.this.initialiseRoam();
            }
        });
    }

    protected void initialiseRoam() {
        Context context = getContext();

        Transform transform = new Transform(mNativeRoamView);
        mRoamGestureDetector = new RoamGestureDetector(context, transform);

        setClickable(true);
        setLongClickable(true);
        setFocusable(true);
        setFocusableInTouchMode(true);
        requestDisallowInterceptTouchEvent(true);
    }


    @Override
    public boolean onTouchEvent(MotionEvent event) {
        if (mRoamGestureDetector == null) {
            return super.onTouchEvent(event);
        }
        return mRoamGestureDetector.onTouchEvent(event) || super.onTouchEvent(event);
    }

    public void onStart() {
        if (mRoamRenderer != null) {
            mRoamRenderer.onStart();
        }
    }

    public void onResume() {
        if (mRoamRenderer != null) {
            mRoamRenderer.onResume();
        }
    }

    public void onPause() {
        if (mRoamRenderer != null) {
            mRoamRenderer.onPause();
        }
    }

    public void onStop() {
        if (mRoamRenderer != null) {
            mRoamRenderer.onStop();
        }
    }

    public void onDestroy() {
        if (mRoamRenderer != null) {
            mRoamRenderer.onDestroy();
        }
    }

}
