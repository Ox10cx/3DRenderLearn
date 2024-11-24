package com.gx.kotlin.scene.roam;

import android.content.Context;
import android.graphics.PointF;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;

import com.gx.kotlin.scene.camera.CameraPosition;
import com.gx.kotlin.scene.geometry.WayPoint;
import com.gx.kotlin.scene.geometry.WayPointBounds;
import com.gx.kotlin.scene.roam.renderer.RoamRenderer;

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
    public double getBearing() {
        return nativeGetBearing();
    }

    @Override
    public void setBearing(double degrees, double fx, double fy, long duration) {
        nativeSetBearingXY(degrees, fx / pixelRatio, fy / pixelRatio, duration);
    }

    @Override
    public double getPitch() {
        return nativeGetPitch();
    }

    @Override
    public void setLatLngBounds(@Nullable WayPointBounds wayPointBounds) {
        nativeSetWayPointBounds(wayPointBounds);
    }

    @Override
    public void setPitch(double pitch, long duration) {
        nativeSetPitch(pitch, duration);
    }

    @Override
    public double getZoom() {
        return nativeGetZoom();
    }

    @Override
    public void setZoom(double zoom, @NonNull PointF focalPoint, long duration) {
        nativeSetZoom(zoom, focalPoint.x / pixelRatio, focalPoint.y / pixelRatio, duration);
    }

    @Override
    public void setMinZoom(double zoom) {
        nativeSetMinZoom(zoom);
    }

    @Override
    public double getMinZoom() {
        return nativeGetMinZoom();
    }

    @Override
    public void setMaxZoom(double zoom) {
        nativeSetMaxZoom(zoom);
    }

    @Override
    public double getMaxZoom() {
        return nativeGetMaxZoom();
    }


    @Override
    public void resizeView(int width, int height) {
        width =  (int) Math.ceil(width / pixelRatio);
        height = (int) Math.ceil(height / pixelRatio);

        nativeResizeView(width, height);
    }

    @Override
    public void setWayPoint(@NonNull WayPoint wayPoint, long duration) {
        nativeSetWayPoint(wayPoint.getX(), wayPoint.getY(), duration);
    }

    @Override
    public CameraPosition getCameraPosition() {
        return nativeGetCameraPosition();
    }

    @Override
    public CameraPosition getCameraForWayPointBounds(WayPointBounds bounds, int[] padding, double bearing, double tilt) {
        return nativeGetCameraForWayPointBounds(
                bounds,
                padding[1] / pixelRatio,
                padding[0] / pixelRatio,
                padding[3] / pixelRatio,
                padding[2] / pixelRatio,
                bearing,
                tilt
        );
    }

    @Override
    public void jumpTo(@NonNull WayPoint center, double zoom, double pitch, double angle) {
        nativeJumpTo(angle, center.getX(), center.getY(), pitch, zoom);
    }

    @Override
    public void easeTo(@NonNull WayPoint center, double zoom, double angle, double pitch, long duration,
                       boolean easingInterpolator) {
        nativeEaseTo(angle, center.getX(), center.getY(), duration, pitch, zoom,
                easingInterpolator);
    }

    @NonNull
    @Override
    public PointF pixelForWayPoint(@NonNull WayPoint wayPoint) {
        PointF pointF = nativePixelForWayPoint(wayPoint.getX(), wayPoint.getY());
        pointF.set(pointF.x * pixelRatio, pointF.y * pixelRatio);
        return pointF;
    }

    @Override
    public WayPoint wayPointForPixel(@NonNull PointF pixel) {
        return nativeWayPointForPixel(pixel.x / pixelRatio, pixel.y / pixelRatio);
    }


    private native void nativeInitialize(NativeRoamView nativeRoamView, RoamRenderer mapRenderer, float pixelRatio);

    private native void nativeDestroy();

    private native void nativeResizeView(int width, int height);

    private native void nativeMoveBy(double deltaX, double deltaY, long duration);

    private native void nativeSetBearingXY(double degrees, double fx, double fy, long duration);

    private native double nativeGetBearing();

    private native double nativeGetPitch();

    private native void nativeSetPitch(double pitch, long duration);

    private native void nativeSetZoom(double zoom, double cx, double cy, long duration);

    private native double nativeGetZoom();

    private native void nativeSetMinZoom(double zoom);

    private native double nativeGetMinZoom();

    private native void nativeSetMaxZoom(double zoom);

    private native double nativeGetMaxZoom();

    private native void nativeSetWayPoint(double wayPointX, double wayPointY, long duration);

    private native CameraPosition nativeGetCameraPosition();

    private native void nativeJumpTo(double angle, double x, double y, double pitch, double zoom);

    private native void nativeEaseTo(double angle, double x, double y,
                                     long duration, double pitch, double zoom,
                                     boolean easingInterpolator);

    private native void nativeSetWayPointBounds(WayPointBounds latLngBounds);

    private native CameraPosition nativeGetCameraForWayPointBounds(
            WayPointBounds wayPointBounds, double top, double left, double bottom, double right, double bearing, double tilt);

    private native PointF nativePixelForWayPoint(double x, double y);

    private native WayPoint nativeWayPointForPixel(float x, float y);


}

