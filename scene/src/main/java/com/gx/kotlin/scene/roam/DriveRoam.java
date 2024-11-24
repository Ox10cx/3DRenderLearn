package com.gx.kotlin.scene.roam;

import android.graphics.PointF;

import androidx.annotation.FloatRange;
import androidx.annotation.NonNull;
import androidx.annotation.Nullable;
import androidx.annotation.Size;

import com.gx.kotlin.scene.camera.CameraPosition;
import com.gx.kotlin.scene.camera.CameraUpdate;
import com.gx.kotlin.scene.camera.CameraUpdateFactory;
import com.gx.kotlin.scene.constants.RoamConstants;
import com.gx.kotlin.scene.geometry.WayPointBounds;


public class DriveRoam {

    private final NativeRoam mNativeRoamView;;
    private final Transform mTransform;
    private final Projection mProjection;

    DriveRoam(NativeRoam roam, Transform transform, Projection projection) {
        this.mNativeRoamView = roam;
        this.mTransform = transform;
        this.mProjection = projection;
    }

    /**
     * Called before the OnMapReadyCallback is invoked.
     */
    void onPreMapReady() {
        mTransform.invalidateCameraPosition();
    }

    /**
     * Called when the OnMapReadyCallback has finished executing.
     * <p>
     * Invalidation of the camera position is required to update the added components in
     * OnMapReadyCallback with the correct transformation.
     * </p>
     */
    void onPostMapReady() {
        mTransform.invalidateCameraPosition();
    }


    public void setMinZoomPreference(
            @FloatRange(from = RoamConstants.MINIMUM_ZOOM, to = RoamConstants.MAXIMUM_ZOOM) double minZoom) {
        mTransform.setMinZoom(minZoom);
    }

    public double getMinZoomLevel() {
        return mTransform.getMinZoom();
    }

    public void zoomBy(double zoomAddition, @NonNull PointF focalPoint) {
        mTransform.zoomBy(zoomAddition, focalPoint);
    }

    public void setMaxZoomPreference(@FloatRange(from = RoamConstants.MINIMUM_ZOOM,
            to = RoamConstants.MAXIMUM_ZOOM) double maxZoom) {
        mTransform.setMaxZoom(maxZoom);
    }

    public double getMaxZoomLevel() {
        return mTransform.getMaxZoom();
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

    public final void easeCamera(@NonNull CameraUpdate update) {
        easeCamera(update, RoamConstants.ANIMATION_DURATION);
    }

    public final void easeCamera(@NonNull CameraUpdate update, int durationMs) {
        easeCamera(update, durationMs, true);
    }

    public final void easeCamera(@NonNull final CameraUpdate update,
                                 final int durationMs,
                                 final boolean easingInterpolator) {
        if (durationMs <= 0) {
            throw new IllegalArgumentException("Null duration passed into easeCamera");
        }
        mTransform.easeCamera(DriveRoam.this, update, durationMs, easingInterpolator);
    }

    public void scrollBy(float x, float y) {
        scrollBy(x, y, 0);
    }

    public void scrollBy(float x, float y, long duration) {
        mNativeRoamView.moveBy(x, y, duration);
    }

    public void setFocalBearing(double bearing, float focalX, float focalY, long duration) {
        mNativeRoamView.setBearing(bearing, focalX, focalY, duration);
    }

    public void setWayPointBoundsForCameraTarget(@Nullable WayPointBounds latLngBounds) {
        mNativeRoamView.setLatLngBounds(latLngBounds);
    }

    @Nullable
    public CameraPosition getCameraForWayPointBounds(@NonNull WayPointBounds wayPointBounds) {
        // we use current camera tilt value to provide expected transformations as #11993
        return getCameraForWayPointBounds(wayPointBounds, new int[] {0, 0, 0, 0});
    }

    @Nullable
    public CameraPosition getCameraForWayPointBounds(@NonNull WayPointBounds wayPointBounds,
                                                   @NonNull @Size(value = 4) int[] padding) {
        // we use current camera tilt/bearing value to provide expected transformations as #11993
        return getCameraForWayPointBounds(wayPointBounds, padding, mTransform.getRawBearing(), mTransform.getTilt());
    }

    @Nullable
    public CameraPosition getCameraForWayPointBounds(@NonNull WayPointBounds wayPointBounds,
                                                   @FloatRange(from = RoamConstants.MINIMUM_DIRECTION,
                                                           to = RoamConstants.MAXIMUM_DIRECTION) double bearing,
                                                   @FloatRange(from = RoamConstants.MINIMUM_TILT,
                                                           to = RoamConstants.MAXIMUM_TILT) double tilt) {
        return getCameraForWayPointBounds(wayPointBounds, new int[] {0, 0, 0, 0}, bearing, tilt);
    }

    @Nullable
    public CameraPosition getCameraForWayPointBounds(@NonNull WayPointBounds wayPointBounds,
                                                   @NonNull @Size(value = 4) int[] padding,
                                                   @FloatRange(from = RoamConstants.MINIMUM_DIRECTION,
                                                           to = RoamConstants.MAXIMUM_DIRECTION) double bearing,
                                                   @FloatRange(from = RoamConstants.MINIMUM_TILT,
                                                           to = RoamConstants.MAXIMUM_TILT) double tilt) {
        return mNativeRoamView.getCameraForWayPointBounds(wayPointBounds, padding, bearing, tilt);
    }

    @NonNull
    public Projection getProjection() {
        return mProjection;
    }
}
