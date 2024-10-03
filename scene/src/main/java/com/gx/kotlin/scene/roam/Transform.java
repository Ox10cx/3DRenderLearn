package com.gx.kotlin.scene.roam;

import android.graphics.PointF;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;
import androidx.annotation.UiThread;

import com.gx.kotlin.scene.camera.CameraPosition;
import com.gx.kotlin.scene.camera.CameraUpdate;

public final class Transform {
    private final NativeRoam mNativeRoam;
    private CameraPosition mCameraPosition;

    public Transform(NativeRoam nativeRoam) {
        this.mNativeRoam = nativeRoam;
    }


    public void moveBy(double offsetX, double offsetY, long duration) {
        mNativeRoam.moveBy(offsetX, offsetY, duration);
    }

    public void setBearing(double bearing, float focalX, float focalY) {
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

    @UiThread
    public final void moveCamera(@NonNull DriveRoam driveRoam, CameraUpdate update) {
        CameraPosition cameraPosition = update.getCameraPosition(driveRoam);
        if (isValidCameraPosition(cameraPosition)) {
            mNativeRoam.jumpTo(cameraPosition.target, cameraPosition.zoom, cameraPosition.tilt, cameraPosition.bearing);
            invalidateCameraPosition();
        }
    }


    @Nullable
    @UiThread
    public final CameraPosition getCameraPosition() {
        if (mCameraPosition == null) {
            mCameraPosition = invalidateCameraPosition();
        }
        return mCameraPosition;
    }

    private boolean isValidCameraPosition(@Nullable CameraPosition cameraPosition) {
        return cameraPosition != null && !cameraPosition.equals(this.mCameraPosition);
    }

    @UiThread
    @Nullable
    CameraPosition invalidateCameraPosition() {
        if (mNativeRoam != null) {
            CameraPosition cameraPosition = mNativeRoam.getCameraPosition();
            this.mCameraPosition = cameraPosition;
        }
        return mCameraPosition;
    }


}
