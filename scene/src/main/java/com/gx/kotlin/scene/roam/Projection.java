package com.gx.kotlin.scene.roam;

import android.graphics.PointF;

import androidx.annotation.NonNull;

import com.gx.kotlin.scene.geometry.WayPoint;

public class Projection {
    private final NativeRoam mNativeRoamView;
    private final RoamView mRoamView;

    Projection(@NonNull NativeRoam nativeRoamView, @NonNull RoamView roamView) {
        this.mNativeRoamView = nativeRoamView;
        this.mRoamView = roamView;
    }

    @NonNull
    public WayPoint fromScreenLocation(@NonNull PointF point) {
        return mNativeRoamView.wayPointForPixel(point);
    }
}
