package com.gx.kotlin.scene.roam;

import android.graphics.PointF;

import androidx.annotation.NonNull;

public interface NativeRoam {

    void moveBy(double deltaX, double deltaY, long duration);

    void setBearing(double degrees, double fx, double fy, long duration);

    void setPitch(double pitch, long duration);

    void setZoom(double zoom, @NonNull PointF focalPoint, long duration);
}
