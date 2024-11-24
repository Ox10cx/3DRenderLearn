package com.gx.kotlin.scene.roam;

import android.graphics.PointF;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;
import androidx.annotation.UiThread;

import com.gx.kotlin.scene.camera.CameraPosition;
import com.gx.kotlin.scene.camera.CameraUpdate;
import com.gx.kotlin.scene.constants.RoamConstants;
import com.gx.kotlin.scene.geometry.WayPoint;
import com.gx.kotlin.scene.log.Logger;

public final class Transform {
    private static final String TAG = "Transform";
    private final NativeRoam mNativeRoam;
    private CameraPosition mCameraPosition;

    public Transform(NativeRoam nativeRoam) {
        this.mNativeRoam = nativeRoam;
    }


    public void moveBy(double offsetX, double offsetY, long duration) {
        mNativeRoam.moveBy(offsetX, offsetY, duration);
    }

    double getRawBearing() {
        return mNativeRoam.getBearing();
    }

    public void setBearing(double bearing, float focalX, float focalY) {
        mNativeRoam.setBearing(bearing, focalX, focalY, 0);
    }

    double getTilt() {
        return mNativeRoam.getPitch();
    }

    public void setPitch(double pitch) {
        mNativeRoam.setPitch(pitch, 0);
    }

    public double getRawZoom() { return mNativeRoam.getZoom(); }

    public void zoomBy(double zoomAddition, @NonNull PointF focalPoint) {
        setZoom(mNativeRoam.getZoom() + zoomAddition, focalPoint);
    }

    public void setZoom(double zoom, @NonNull PointF focalPoint) {
        mNativeRoam.setZoom(zoom, focalPoint, 0);
    }

    public void setCenterCoordinate(WayPoint centerCoordinate) {
        mNativeRoam.setWayPoint(centerCoordinate, 0);
    }


    @UiThread
    public final void moveCamera(@NonNull DriveRoam driveRoam, CameraUpdate update) {
        CameraPosition cameraPosition = update.getCameraPosition(driveRoam);
        if (isValidCameraPosition(cameraPosition)) {
            mNativeRoam.jumpTo(cameraPosition.target, cameraPosition.zoom, cameraPosition.tilt, cameraPosition.bearing);
            invalidateCameraPosition();
        }
    }

    @UiThread
    final void easeCamera(@NonNull DriveRoam driveRoam, CameraUpdate update, int durationMs, boolean easingInterpolator) {
        CameraPosition cameraPosition = update.getCameraPosition(driveRoam);
        if (isValidCameraPosition(cameraPosition)) {
            mNativeRoam.easeTo(cameraPosition.target, cameraPosition.zoom, cameraPosition.bearing, cameraPosition.tilt,
                    durationMs, easingInterpolator);
        }
    }


    @Nullable
    @UiThread
    public CameraPosition getCameraPosition() {
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

    public void setMinZoom(double minZoom) {
        if ((minZoom < RoamConstants.MINIMUM_ZOOM) || (minZoom > RoamConstants.MAXIMUM_ZOOM)) {
            Logger.e(TAG, String.format("Not setting minZoomPreference, value is in unsupported range: %s", minZoom));
            return;
        }
        mNativeRoam.setMinZoom(minZoom);
    }

    public double getMinZoom() {
        return mNativeRoam.getMinZoom();
    }

    public void setMaxZoom(double maxZoom) {
        if ((maxZoom < RoamConstants.MINIMUM_ZOOM) || (maxZoom > RoamConstants.MAXIMUM_ZOOM)) {
            Logger.e(TAG, String.format("Not setting maxZoomPreference, value is in unsupported range: %s", maxZoom));
            return;
        }
        mNativeRoam.setMaxZoom(maxZoom);
    }

    public double getMaxZoom() {
        return mNativeRoam.getMaxZoom();
    }

}
