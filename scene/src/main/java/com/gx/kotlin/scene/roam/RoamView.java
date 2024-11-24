package com.gx.kotlin.scene.roam;

import android.content.Context;
import android.util.AttributeSet;
import android.view.MotionEvent;
import android.widget.FrameLayout;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;
import androidx.annotation.UiThread;

import com.gx.kotlin.scene.roam.renderer.RoamRenderer;
import com.gx.kotlin.scene.roam.renderer.glsurfaceview.GLSurfaceViewRoamRenderer;
import com.gx.kotlin.scene.roam.renderer.glsurfaceview.RoamGLSurfaceView;

import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

public class RoamView extends FrameLayout {
    private RoamRenderer mRoamRenderer;
    private NativeRoam mNativeRoamView;
    private RoamGestureDetector mRoamGestureDetector;
    private DriveRoam mDriveRoam;

    private final RoamCallback mRoamCallback = new RoamCallback();

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


        Projection proj = new Projection(mNativeRoamView, this);
        Transform transform = new Transform(mNativeRoamView);
        mRoamGestureDetector = new RoamGestureDetector(context, transform);
        mDriveRoam = new DriveRoam(mNativeRoamView, transform, proj);


        setClickable(true);
        setLongClickable(true);
        setFocusable(true);
        setFocusableInTouchMode(true);
        requestDisallowInterceptTouchEvent(true);

        mRoamCallback.initialised();
    }


    @Override
    public boolean onTouchEvent(MotionEvent event) {
        if (mRoamGestureDetector == null) {
            return super.onTouchEvent(event);
        }
        return mRoamGestureDetector.onTouchEvent(event) || super.onTouchEvent(event);
    }

    @Override
    protected void onSizeChanged(int w, int h, int oldw, int oldh) {
        if (!isInEditMode() && mNativeRoamView != null) {
            // null-checking the nativeMapView, see #13277
            mNativeRoamView.resizeView(w, h);
        }
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
        mRoamCallback.onDestroy();
    }

    @UiThread
    public void getRoamAsync(final @NonNull OnRoamReadyCallback callback) {
        if (mDriveRoam == null) {
            // Add callback to the list only if the style hasn't loaded, or the drawing surface isn't ready
            mRoamCallback.addOnMapReadyCallback(callback);
        } else {
            callback.onMapReady(mDriveRoam);
        }
    }


    private class RoamCallback {
        private final List<OnRoamReadyCallback> onMapReadyCallbackList = new ArrayList<>();

        void initialised() {
            mDriveRoam.onPreMapReady();
            onMapReady();
            mDriveRoam.onPostMapReady();
        }

        private void onMapReady() {
            if (onMapReadyCallbackList.size() > 0) {
                Iterator<OnRoamReadyCallback> iterator = onMapReadyCallbackList.iterator();
                while (iterator.hasNext()) {
                    OnRoamReadyCallback callback = iterator.next();
                    if (callback != null) {
                        // null checking required for #13279
                        callback.onMapReady(mDriveRoam);
                    }
                    iterator.remove();
                }
            }
        }

        void addOnMapReadyCallback(OnRoamReadyCallback callback) {
            onMapReadyCallbackList.add(callback);
        }

        void onDestroy() {
            onMapReadyCallbackList.clear();
        }

    }



}
