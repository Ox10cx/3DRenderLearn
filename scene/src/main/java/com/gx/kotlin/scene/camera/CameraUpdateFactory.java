package com.gx.kotlin.scene.camera;

import android.graphics.Point;
import android.graphics.PointF;

import androidx.annotation.IntDef;
import androidx.annotation.NonNull;
import androidx.annotation.Nullable;

import com.gx.kotlin.scene.geometry.WayPoint;
import com.gx.kotlin.scene.geometry.WayPointBounds;
import com.gx.kotlin.scene.log.Logger;
import com.gx.kotlin.scene.roam.DriveRoam;

import java.lang.annotation.Retention;
import java.lang.annotation.RetentionPolicy;
import java.util.Arrays;

public final class CameraUpdateFactory {

    public static CameraUpdate newCameraPosition(@NonNull CameraPosition cameraPosition) {
        return new CameraPositionUpdate(cameraPosition.bearing, cameraPosition.target, cameraPosition.tilt,
                cameraPosition.zoom);
    }

    public static CameraUpdate newWayPoint(@NonNull WayPoint point) {
        return new CameraPositionUpdate(-1, point, -1, -1);
    }

    public static CameraUpdate newWayPointBounds(@NonNull WayPointBounds bounds, int padding) {
        return newWayPointBounds(bounds, padding, padding, padding, padding);
    }


    public static CameraUpdate newWayPointBounds(@NonNull WayPointBounds bounds, double bearing, double tilt, int padding) {
        return newWayPointBounds(bounds, bearing, tilt, padding, padding, padding, padding);
    }

    public static CameraUpdate newWayPointBounds(@NonNull WayPointBounds bounds, int paddingLeft, int paddingTop,
                                               int paddingRight, int paddingBottom) {
        return new CameraBoundsUpdate(bounds, null, null, paddingLeft, paddingTop, paddingRight, paddingBottom);
    }


    public static CameraUpdate newWayPointZoom(@NonNull WayPoint point, double zoom) {
        return new CameraPositionUpdate(-1, point, -1, zoom);
    }

    public static CameraUpdate newWayPointBounds(@NonNull WayPointBounds bounds, double bearing, double tilt,
                                                 int paddingLeft, int paddingTop, int paddingRight, int paddingBottom) {
        return new CameraBoundsUpdate(bounds, bearing, tilt, paddingLeft, paddingTop, paddingRight, paddingBottom);
    }


    public static CameraUpdate zoomBy(double amount, Point focus) {
        return new ZoomUpdate(amount, focus.x, focus.y);
    }

    public static CameraUpdate zoomBy(double amount) {
        return new ZoomUpdate(ZoomUpdate.ZOOM_BY, amount);
    }


    public static CameraUpdate zoomIn() {
        return new ZoomUpdate(ZoomUpdate.ZOOM_IN);
    }


    public static CameraUpdate zoomOut() {
        return new ZoomUpdate(ZoomUpdate.ZOOM_OUT);
    }


    public static CameraUpdate zoomTo(double zoom) {
        return new ZoomUpdate(ZoomUpdate.ZOOM_TO, zoom);
    }


    public static CameraUpdate bearingTo(double bearing) {
        return new CameraPositionUpdate(bearing, null, -1, -1);
    }


    public static CameraUpdate tiltTo(double tilt) {
        return new CameraPositionUpdate(-1, null, tilt, -1);
    }


    //
    // CameraUpdate types
    //

    static final class CameraPositionUpdate implements CameraUpdate {

        private final double bearing;
        private final WayPoint target;
        private final double tilt;
        private final double zoom;

        CameraPositionUpdate(double bearing, WayPoint target, double tilt, double zoom) {
            this.bearing = bearing;
            this.target = target;
            this.tilt = tilt;
            this.zoom = zoom;
        }

        public WayPoint getTarget() {
            return target;
        }

        public double getBearing() {
            return bearing;
        }

        public double getTilt() {
            return tilt;
        }

        public double getZoom() {
            return zoom;
        }

        @Override
        public CameraPosition getCameraPosition(@NonNull DriveRoam driveRoam) {
            CameraPosition previousPosition = driveRoam.getCameraPosition();
            if (target == null) {
                return new CameraPosition.Builder(this)
                        .target(previousPosition.target)
                        .build();
            }
            return new CameraPosition.Builder(this).build();
        }

        @Override
        public boolean equals(@Nullable Object o) {
            if (this == o) {
                return true;
            }
            if (o == null || getClass() != o.getClass()) {
                return false;
            }

            CameraPositionUpdate that = (CameraPositionUpdate) o;

            if (Double.compare(that.bearing, bearing) != 0) {
                return false;
            }
            if (Double.compare(that.tilt, tilt) != 0) {
                return false;
            }
            if (Double.compare(that.zoom, zoom) != 0) {
                return false;
            }
            return target != null ? target.equals(that.target) : that.target == null;
        }

        @Override
        public int hashCode() {
            int result;
            long temp;
            temp = Double.doubleToLongBits(bearing);
            result = (int) (temp ^ (temp >>> 32));
            result = 31 * result + (target != null ? target.hashCode() : 0);
            temp = Double.doubleToLongBits(tilt);
            result = 31 * result + (int) (temp ^ (temp >>> 32));
            temp = Double.doubleToLongBits(zoom);
            result = 31 * result + (int) (temp ^ (temp >>> 32));
            return result;
        }

        @Override
        public String toString() {
            return "CameraPositionUpdate{"
                    + "bearing=" + bearing
                    + ", target=" + target
                    + ", tilt=" + tilt
                    + ", zoom=" + zoom
                    + '}';
        }
    }

    static final class CameraBoundsUpdate implements CameraUpdate {

        private final WayPointBounds bounds;
        private final int[] padding;
        private final Double bearing;
        private final Double tilt;

        CameraBoundsUpdate(WayPointBounds bounds, Double bearing, Double tilt, int[] padding) {
            this.bounds = bounds;
            this.padding = padding;
            this.bearing = bearing;
            this.tilt = tilt;
        }

        CameraBoundsUpdate(WayPointBounds bounds, Double bearing, Double tilt, int paddingLeft,
                           int paddingTop, int paddingRight, int paddingBottom) {
            this(bounds, bearing, tilt, new int[] {paddingLeft, paddingTop, paddingRight, paddingBottom});
        }

        public WayPointBounds getBounds() {
            return bounds;
        }

        public int[] getPadding() {
            return padding;
        }

        @Override
        public CameraPosition getCameraPosition(@NonNull DriveRoam driveRoam) {
            if (bearing == null && tilt == null) {
                // use current camera position tilt and bearing
                return driveRoam.getCameraForWayPointBounds(bounds, padding);
            } else {
                // use provided tilt and bearing
                assert bearing != null;
                assert tilt != null;
                return driveRoam.getCameraForWayPointBounds(bounds, padding, bearing, tilt);
            }
        }

        @Override
        public boolean equals(@Nullable Object o) {
            if (this == o) {
                return true;
            }
            if (o == null || getClass() != o.getClass()) {
                return false;
            }

            CameraBoundsUpdate that = (CameraBoundsUpdate) o;

            if (!bounds.equals(that.bounds)) {
                return false;
            }
            return Arrays.equals(padding, that.padding);
        }

        @Override
        public int hashCode() {
            int result = bounds.hashCode();
            result = 31 * result + Arrays.hashCode(padding);
            return result;
        }

        @Override
        public String toString() {
            return "CameraBoundsUpdate{"
                    + "bounds=" + bounds
                    + ", padding=" + Arrays.toString(padding)
                    + '}';
        }
    }


    static final class ZoomUpdate implements CameraUpdate {

        @IntDef( {ZOOM_IN, ZOOM_OUT, ZOOM_BY, ZOOM_TO, ZOOM_TO_POINT})
        @Retention(RetentionPolicy.SOURCE)
        @interface Type {
        }

        static final int ZOOM_IN = 0;
        static final int ZOOM_OUT = 1;
        static final int ZOOM_BY = 2;
        static final int ZOOM_TO = 3;
        static final int ZOOM_TO_POINT = 4;

        @Type
        private final int type;
        private final double zoom;
        private float x;
        private float y;

        ZoomUpdate(@Type int type) {
            this.type = type;
            this.zoom = 0;
        }

        ZoomUpdate(@Type int type, double zoom) {
            this.type = type;
            this.zoom = zoom;
        }

        ZoomUpdate(double zoom, float x, float y) {
            this.type = ZOOM_TO_POINT;
            this.zoom = zoom;
            this.x = x;
            this.y = y;
        }

        public double getZoom() {
            return zoom;
        }

        @Type
        public int getType() {
            return type;
        }

        public float getX() {
            return x;
        }

        public float getY() {
            return y;
        }

        double transformZoom(double currentZoom) {
            switch (getType()) {
                case CameraUpdateFactory.ZoomUpdate.ZOOM_IN:
                    currentZoom++;
                    break;
                case CameraUpdateFactory.ZoomUpdate.ZOOM_OUT:
                    currentZoom--;
                    if (currentZoom < 0) {
                        currentZoom = 0;
                    }
                    break;
                case CameraUpdateFactory.ZoomUpdate.ZOOM_TO:
                    currentZoom = getZoom();
                    break;
                case CameraUpdateFactory.ZoomUpdate.ZOOM_BY:
                    currentZoom = currentZoom + getZoom();
                    break;
                case CameraUpdateFactory.ZoomUpdate.ZOOM_TO_POINT:
                    currentZoom = currentZoom + getZoom();
                    break;
            }
            return currentZoom;
        }

        @Override
        public CameraPosition getCameraPosition(@NonNull DriveRoam driveRoam) {
            CameraPosition cameraPosition = driveRoam.getCameraPosition();
            if (getType() != CameraUpdateFactory.ZoomUpdate.ZOOM_TO_POINT) {
                return new CameraPosition.Builder(cameraPosition)
                        .zoom(transformZoom(cameraPosition.zoom))
                        .build();
            } else {
                return new CameraPosition.Builder(cameraPosition)
                        .zoom(transformZoom(cameraPosition.zoom))
                        .target(driveRoam.getProjection().fromScreenLocation(new PointF(getX(), getY())))
                        .build();
            }
        }

        @Override
        public boolean equals(@Nullable Object o) {
            if (this == o) {
                return true;
            }
            if (o == null || getClass() != o.getClass()) {
                return false;
            }

            ZoomUpdate that = (ZoomUpdate) o;

            if (type != that.type) {
                return false;
            }
            if (Double.compare(that.zoom, zoom) != 0) {
                return false;
            }
            if (Float.compare(that.x, x) != 0) {
                return false;
            }
            return Float.compare(that.y, y) == 0;
        }

        @Override
        public int hashCode() {
            int result;
            long temp;
            result = type;
            temp = Double.doubleToLongBits(zoom);
            result = 31 * result + (int) (temp ^ (temp >>> 32));
            result = 31 * result + (x != +0.0f ? Float.floatToIntBits(x) : 0);
            result = 31 * result + (y != +0.0f ? Float.floatToIntBits(y) : 0);
            return result;
        }

        @Override
        public String toString() {
            return "ZoomUpdate{"
                    + "type=" + type
                    + ", zoom=" + zoom
                    + ", x=" + x
                    + ", y=" + y
                    + '}';
        }
    }

}