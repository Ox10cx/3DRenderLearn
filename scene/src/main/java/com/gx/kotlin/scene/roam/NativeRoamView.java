package com.gx.kotlin.scene.roam;

import android.content.Context;
import android.graphics.PointF;

import androidx.annotation.NonNull;

import com.gx.kotlin.scene.roam.render.RoamRenderer;

public final class NativeRoamView implements NativeRoam {

    private final RoamRenderer mRoamRenderer;

    // Device density
    private final float pixelRatio;

    private long nativePtr = 0;

    public NativeRoamView(final Context context, final RoamRenderer roamRenderer) {
        this.pixelRatio = context.getResources().getDisplayMetrics().density;
        this.mRoamRenderer = roamRenderer;
        nativeInitialize(this, mRoamRenderer, pixelRatio);
    }

    @Override
    public void moveBy(double deltaX, double deltaY, long duration) {
        nativeMoveBy(deltaX, deltaY, duration);
    }

    @Override
    public void setBearing(double degrees, double fx, double fy, long duration) {
        nativeSetBearingXY(degrees, fx / pixelRatio, fy / pixelRatio, duration);
    }

    @Override
    public void setPitch(double pitch, long duration) {
        nativeSetPitch(pitch, duration);
    }

    @Override
    public void setZoom(double zoom, @NonNull PointF focalPoint, long duration) {
        nativeSetZoom(zoom, focalPoint.x / pixelRatio, focalPoint.y / pixelRatio, duration);
    }

    @Override
    public void resizeView(int width, int height) {
        width =  (int) Math.ceil(width / pixelRatio);
        height = (int) Math.ceil(height / pixelRatio);

        nativeResizeView(width, height);
    }


    private native void nativeInitialize(NativeRoamView nativeRoamView, RoamRenderer mapRenderer, float pixelRatio);

    private native void nativeDestroy();

    private native void nativeResizeView(int width, int height);

    private native void nativeMoveBy(double deltaX, double deltaY, long duration);

    private native void nativeSetBearingXY(double degrees, double fx, double fy, long duration);

    private native void nativeSetPitch(double pitch, long duration);

    private native void nativeSetZoom(double zoom, double cx, double cy, long duration);

}

