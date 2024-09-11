package com.gx.kotlin.scene.roam;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;

import com.gx.kotlin.scene.camera.CameraPosition;
import com.gx.kotlin.scene.camera.CameraUpdate;
import com.gx.kotlin.scene.camera.CameraUpdateFactory;


public class DriveRoam {

    private final NativeRoam mNativeRoamView;;
    private final Transform mTransform;

    DriveRoam(NativeRoam roam, Transform transform) {
        this.mNativeRoamView = roam;
        this.mTransform = transform;
    }

    public CameraPosition getCameraPosition() {
        return mTransform.getCameraPosition();
    }

    public void setCameraPosition(@NonNull CameraPosition cameraPosition) {
        moveCamera(CameraUpdateFactory.newCameraPosition(cameraPosition));
    }

    public final void moveCamera(@NonNull CameraUpdate update) {
        mTransform.moveCamera(DriveRoam.this, update);
    }


    public void scrollBy(float x, float y, long duration) {
        mNativeRoamView.moveBy(x, y, duration);
    }

    public void setFocalBearing(double bearing, float focalX, float focalY, long duration) {
        mNativeRoamView.setBearing(bearing, focalX, focalY, duration);
    }



}
