package com.gx.kotlin.scene.camera;

import android.os.Parcel;
import android.os.Parcelable;

import androidx.annotation.FloatRange;
import androidx.annotation.Keep;
import androidx.annotation.NonNull;
import androidx.annotation.Nullable;
import androidx.core.math.MathUtils;

import com.gx.kotlin.scene.constants.RoamConstants;
import com.gx.kotlin.scene.geometry.WayPoint;

public final class CameraPosition implements Parcelable {

    public static final CameraPosition DEFAULT = new CameraPosition(new WayPoint(), 0, 0, 0);

    public static final Parcelable.Creator<CameraPosition> CREATOR =
            new Parcelable.Creator<CameraPosition>() {
                public CameraPosition createFromParcel(Parcel in) {
                    double bearing = in.readDouble();
                    WayPoint target = in.readParcelable(WayPoint.class.getClassLoader());
                    double tilt = in.readDouble();
                    double zoom = in.readDouble();
                    return new CameraPosition(target, zoom, tilt, bearing);
                }

                public CameraPosition[] newArray(int size) {
                    return new CameraPosition[size];
                }
            };

    @Keep
    public final double bearing;


    @Keep
    public final WayPoint target;


    @Keep
    public final double tilt;


    @Keep
    public final double zoom;


    @Keep
    CameraPosition(WayPoint target, double zoom, double tilt, double bearing) {
        this.target = target;
        this.bearing = bearing;
        this.tilt = tilt;
        this.zoom = zoom;
    }

    @Override
    public int describeContents() {
        return 0;
    }


    @Override
    public void writeToParcel(Parcel out, int flags) {
        out.writeDouble(bearing);
        out.writeParcelable(target, flags);
        out.writeDouble(tilt);
        out.writeDouble(zoom);
    }


    @Override
    public String toString() {
        return "Target: " + target + ", Zoom:" + zoom + ", Bearing:" + bearing + ", Tilt:" + tilt;
    }

    @Override
    public boolean equals(@Nullable Object o) {
        if (this == o) {
            return true;
        }

        if (o == null || getClass() != o.getClass()) {
            return false;
        }

        CameraPosition cameraPosition = (CameraPosition) o;
        if (target != null && !target.equals(cameraPosition.target)) {
            return false;
        } else if (zoom != cameraPosition.zoom) {
            return false;
        } else if (tilt != cameraPosition.tilt) {
            return false;
        } else if (bearing != cameraPosition.bearing) {
            return false;
        }
        return true;
    }


    @Override
    public int hashCode() {
        int result = 1;
        result = 31 * result + (target != null ? target.hashCode() : 0);
        return result;
    }


    public static final class Builder {

        private double bearing = -1;
        @Nullable
        private WayPoint target = null;
        private double tilt = -1;
        private double zoom = -1;

        /**
         * Create an empty builder.
         */
        public Builder() {
            super();
        }

        /**
         * Create a builder with an existing CameraPosition data.
         *
         * @param previous Existing CameraPosition values to use
         */
        public Builder(@Nullable CameraPosition previous) {
            super();
            if (previous != null) {
                this.bearing = previous.bearing;
                this.target = previous.target;
                this.tilt = previous.tilt;
                this.zoom = previous.zoom;
            }
        }

        /**
         * Create a builder from an existing CameraPositionUpdate update.
         *
         * @param update Update containing camera options
         */
        public Builder(@Nullable CameraUpdateFactory.CameraPositionUpdate update) {
            super();
            if (update != null) {
                bearing = update.getBearing();
                target = update.getTarget();
                tilt = update.getTilt();
                zoom = update.getZoom();
            }
        }

        /**
         * Create builder from an existing CameraPositionUpdate update.
         *
         * @param update Update containing camera options
         */
        public Builder(@Nullable CameraUpdateFactory.ZoomUpdate update) {
            super();
            if (update != null) {
                this.zoom = update.getZoom();
            }
        }

        /**
         * Sets the direction that the camera is pointing in, in degrees clockwise from north.
         *
         * @param bearing Bearing
         * @return this
         */
        @NonNull
        public Builder bearing(double bearing) {
            double direction = bearing;

            while (direction >= 360) {
                direction -= 360;
            }
            while (direction < 0) {
                direction += 360;
            }

            this.bearing = direction;
            return this;
        }


        @NonNull
        public Builder target(WayPoint point) {
            this.target = point;
            return this;
        }


        @NonNull
        public Builder tilt(@FloatRange(from = RoamConstants.MINIMUM_TILT,
                to = RoamConstants.MAXIMUM_TILT) double tilt) {
            this.tilt = MathUtils.clamp(tilt, RoamConstants.MINIMUM_TILT, RoamConstants.MAXIMUM_TILT);
            return this;
        }


        @NonNull
        public Builder zoom(@FloatRange(from = RoamConstants.MINIMUM_ZOOM,
                to = RoamConstants.MAXIMUM_ZOOM) double zoom) {
            this.zoom = zoom;
            return this;
        }

        /**
         * Builds the CameraPosition.
         *
         * @return CameraPosition
         */
        public CameraPosition build() {
            return new CameraPosition(target, zoom, tilt, bearing);
        }
    }
}
