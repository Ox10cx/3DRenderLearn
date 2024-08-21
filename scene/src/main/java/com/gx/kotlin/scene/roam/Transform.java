package com.gx.kotlin.scene.roam;

import android.graphics.PointF;

import androidx.annotation.NonNull;

public final class Transform {
    private final NativeRoam mNativeRoam;

    public Transform(NativeRoam nativeRoam) {
        this.mNativeRoam = nativeRoam;
    }


    void moveBy(double offsetX, double offsetY, long duration) {
        mNativeRoam.moveBy(offsetX, offsetY, duration);
    }

    void setBearing(double bearing, float focalX, float focalY) {
        mNativeRoam.setBearing(bearing, focalX, focalY, 0);
    }

    void setPitch(double pitch) {
        mNativeRoam.setPitch(pitch, 0);
    }

    void zoomBy(double zoomAddition, @NonNull PointF focalPoint) {
        setZoom( zoomAddition, focalPoint);
    }

    void setZoom(double zoom, @NonNull PointF focalPoint) {
        mNativeRoam.setZoom(zoom, focalPoint, 0);
    }



}
