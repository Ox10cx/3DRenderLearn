package com.gx.kotlin.scene.roam;

import android.graphics.PointF;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;

import com.gx.kotlin.scene.camera.CameraPosition;
import com.gx.kotlin.scene.geometry.WayPoint;
import com.gx.kotlin.scene.geometry.WayPointBounds;

public interface NativeRoam {

    void moveBy(double deltaX, double deltaY, long duration);

    double getBearing();

    void setBearing(double degrees, double fx, double fy, long duration);

    void setLatLngBounds(@Nullable WayPointBounds wayPointBounds);

    void setPitch(double pitch, long duration);

    double getPitch();

    double getZoom();

    void setZoom(double zoom, @NonNull PointF focalPoint, long duration);

    void setMinZoom(double zoom);

    double getMinZoom();

    void setMaxZoom(double zoom);

    double getMaxZoom();

    void resizeView(int width, int height);

    void setWayPoint(@NonNull WayPoint wayPoint, long duration);

    CameraPosition getCameraPosition();

    CameraPosition getCameraForWayPointBounds(@NonNull WayPointBounds bounds, int[] padding, double bearing, double pitch);

    void jumpTo(@NonNull WayPoint center, double zoom, double pitch, double bearing);

    void easeTo(@NonNull WayPoint center, double zoom, double bearing, double pitch, long duration,
                boolean easingInterpolator);

    WayPoint wayPointForPixel(@NonNull PointF pixel);

    @NonNull
    PointF pixelForWayPoint(@NonNull WayPoint wayPoint);
}
