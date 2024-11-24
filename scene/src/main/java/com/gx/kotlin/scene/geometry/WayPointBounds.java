package com.gx.kotlin.scene.geometry;

import static com.gx.kotlin.scene.constants.RoamConstants.MAX_WRAP_X;
import static com.gx.kotlin.scene.constants.RoamConstants.MAX_Y;
import static com.gx.kotlin.scene.constants.RoamConstants.MIN_WRAP_X;
import static com.gx.kotlin.scene.constants.RoamConstants.MIN_Y;

import android.os.Parcel;
import android.os.Parcelable;

import androidx.annotation.FloatRange;
import androidx.annotation.Keep;
import androidx.annotation.NonNull;
import androidx.annotation.Nullable;

import com.gx.kotlin.scene.exceptions.InvalidWayPointBoundsException;

import java.util.ArrayList;
import java.util.List;

public class WayPointBounds implements Parcelable {

    @Keep
    private final double yNorth;
    @Keep
    private final double ySouth;
    @Keep
    private final double xEast;
    @Keep
    private final double xWest;

    /**
     *
     * @param northY Northern Y
     * @param eastX Eastern X
     * @param southY Southern Y
     * @param westX Western X
     */
    @Keep
    WayPointBounds(final double northY, final double eastX,
                 final double southY, final double westX) {
        this.yNorth = northY;
        this.xEast = eastX;
        this.ySouth = southY;
        this.xWest = westX;
    }

    /**
     * Returns the world bounds.
     *
     * @return the bounds representing the world
     */
    public static WayPointBounds world() {
        return WayPointBounds.from(
                MAX_WRAP_X, MAX_Y,
                MIN_WRAP_X, MIN_Y);
    }


    @NonNull
    public WayPoint getCenter() {
        double xCenter = (this.xEast + this.xWest) / 2.0;
        double yCenter = (this.yNorth + this.ySouth) / 2.0;

        return new WayPoint(xCenter, yCenter);
    }


    public double getYNorth() {
        return this.yNorth;
    }


    public double getYSouth() {
        return this.ySouth;
    }


    public double getXEast() {
        return this.xEast;
    }


    public double getXWest() {
        return this.xWest;
    }


    @NonNull
    public WayPoint getSouthWest() {
        return new WayPoint(xWest, ySouth);
    }


    @NonNull
    public WayPoint getNorthEast() {
        return new WayPoint(xEast, yNorth);
    }


    @NonNull
    public WayPoint getSouthEast() {
        return new WayPoint(xEast, ySouth);
    }


    @NonNull
    public WayPoint getNorthWest() {
        return new WayPoint(xWest, yNorth);
    }


    @NonNull
    public WayPointSpan getSpan() {
        return new WayPointSpan(getXSpan(), getYSpan());
    }

    public double getYSpan() {
        return Math.abs(this.yNorth - this.ySouth);
    }

    public double getXSpan() {
        return Math.abs(this.xEast - this.xWest);
    }

    public boolean isEmptySpan() {
        return getXSpan() == 0.0 || getYSpan() == 0.0;
    }

    @NonNull
    @Override
    public String toString() {
        return "N:" + this.yNorth + "; E:" + this.xEast + "; S:" + this.ySouth
                + "; W:" + this.xWest;
    }


    static WayPointBounds fromWayPoints(final List<? extends WayPoint> wayPoints) {
        double minY = MAX_Y;
        double minX = MAX_WRAP_X;
        double maxY = MIN_Y;
        double maxX = MIN_WRAP_X;

        for (final WayPoint gp : wayPoints) {
            final double x = gp.getX();
            final double y = gp.getY();
            minY = Math.min(minY, y);
            minX = Math.min(minX, x);
            maxY = Math.max(maxY, y);
            maxX = Math.max(maxX, x);
        }

        return new WayPointBounds(maxY, maxX, minY, minX);
    }

    @NonNull
    public WayPoint[] toWayPoints() {
        return new WayPoint[] {getNorthEast(), getSouthWest()};
    }


    public static WayPointBounds from(
            double xEast,
            @FloatRange(from = MIN_Y, to = MAX_Y) double yNorth,
            double xWest,
            @FloatRange(from = MIN_Y, to = MAX_Y) double ySouth) {

        checkParams(yNorth, xEast, ySouth, xWest);

        return new WayPointBounds(yNorth, xEast, ySouth, xWest);
    }

    private static void checkParams(
            double xEast,
            @FloatRange(from = MIN_Y, to = MAX_Y) double yNorth,
            double xWest,
            @FloatRange(from = MIN_Y, to = MAX_Y) double ySouth) {

        if (Double.isNaN(yNorth) || Double.isNaN(ySouth)) {
            throw new IllegalArgumentException("y must not be NaN");
        }

        if (Double.isNaN(xEast) || Double.isNaN(xWest)) {
            throw new IllegalArgumentException("x must not be NaN");
        }

        if (Double.isInfinite(xEast) || Double.isInfinite(xWest)) {
            throw new IllegalArgumentException("x must not be infinite");
        }

        if (yNorth > MAX_Y || yNorth < MIN_Y
                || ySouth > MAX_Y || ySouth < MIN_Y) {
            throw new IllegalArgumentException("y must be between -90 and 90");
        }

        if (yNorth < ySouth) {
            throw new IllegalArgumentException("yNorth cannot be less than ySouth");
        }

        if (xEast < xWest) {
            throw new IllegalArgumentException("xEast cannot be less than xWest");
        }
    }



    @NonNull
    public WayPointBounds include(@NonNull WayPoint wayPoint) {
        return new WayPointBounds.Builder()
                .include(getNorthEast())
                .include(getSouthWest())
                .include(wayPoint)
                .build();
    }

    @Override
    public boolean equals(final Object o) {
        if (this == o) {
            return true;
        }
        if (o instanceof WayPointBounds) {
            WayPointBounds other = (WayPointBounds) o;
            return yNorth == other.getYNorth()
                    && ySouth == other.getYSouth()
                    && xEast == other.getXEast()
                    && xWest == other.getXWest();
        }
        return false;
    }


    private boolean containsY(final double y) {
        return (y <= this.yNorth)
                && (y >= this.ySouth);
    }

    private boolean containsX(final double x) {
        return (x <= this.xEast)
                && (x >= this.xWest);
    }


    public boolean contains(@NonNull final WayPoint wayPoint) {
        return containsY(wayPoint.getY())
                && containsX(wayPoint.getX());
    }


    public boolean contains(@NonNull final WayPointBounds other) {
        return contains(other.getNorthEast())
                && contains(other.getSouthWest());
    }


    @NonNull
    public WayPointBounds union(@NonNull WayPointBounds bounds) {
        return unionNoParamCheck(bounds.getYNorth(), bounds.getXEast(),
                bounds.getYSouth(), bounds.getXWest());
    }


    @NonNull
    public WayPointBounds union(final double northY, final double eastX,
                              final double southY, final double westX) {
        checkParams(eastX, northY, westX, southY);
        return unionNoParamCheck(northY, eastX, southY, westX);
    }

    private WayPointBounds unionNoParamCheck(final double northY, final double eastX,
                                           final double southY, final double westX) {

        return new WayPointBounds((this.yNorth < northY) ? northY : this.yNorth,
                (this.xEast < eastX) ? eastX : this.xEast,
                (this.ySouth > southY) ? southY : this.ySouth,
                (this.xWest > westX) ? westX : this.xWest);
    }


    @Nullable
    public WayPointBounds intersect(@NonNull WayPointBounds box) {
        return intersectNoParamCheck(box.getYNorth(), box.getXEast(), box.getYSouth(), box.getXWest());
    }


    @NonNull
    public WayPointBounds intersect(final double northY, final double eastX,
                                  final double southY, final double westX) {
        checkParams(eastX, northY, westX, southY);
        return intersectNoParamCheck(northY, eastX, southY, westX);
    }

    private WayPointBounds intersectNoParamCheck(final double northY, final double eastX,
                                               final double southY, final double westX) {

        double minLonWest = Math.max(this.xWest, westX);
        double maxLonEast = Math.min(this.xEast, eastX);
        if (maxLonEast >= minLonWest) {
            double minYSouth = Math.max(this.ySouth, southY);
            double maxYNorth = Math.min(this.yNorth, northY);
            if (maxYNorth >= minYSouth) {
                return new WayPointBounds(maxYNorth, maxLonEast, minYSouth, minLonWest);
            }
        }
        return null;
    }



    /**
     * Inner class responsible for recreating Parcels into objects.
     */
    public static final Parcelable.Creator<WayPointBounds> CREATOR =
            new Parcelable.Creator<WayPointBounds>() {
                @Override
                public WayPointBounds createFromParcel(@NonNull final Parcel in) {
                    return readFromParcel(in);
                }

                @Override
                public WayPointBounds[] newArray(final int size) {
                    return new WayPointBounds[size];
                }
            };

    /**
     * Returns a hash code value for the object.
     *
     * @return the hash code
     */
    @Override
    public int hashCode() {
        return (int) ((yNorth + 90)
                + ((ySouth + 90) * 1000)
                + ((xEast + 180) * 1000000)
                + ((xWest + 180) * 1000000000));
    }

    /**
     * Describe the kinds of special objects contained in this Parcelable instance's marshaled representation.
     *
     * @return a bitmask indicating the set of special object types marshaled by this Parcelable object instance.
     */
    @Override
    public int describeContents() {
        return 0;
    }

    /**
     * Flatten this object in to a Parcel.
     *
     * @param out   The Parcel in which the object should be written.
     * @param flags Additional flags about how the object should be written
     */
    @Override
    public void writeToParcel(@NonNull final Parcel out, final int flags) {
        out.writeDouble(this.yNorth);
        out.writeDouble(this.xEast);
        out.writeDouble(this.ySouth);
        out.writeDouble(this.xWest);
    }

    private static WayPointBounds readFromParcel(final Parcel in) {
        final double northY = in.readDouble();
        final double eastX = in.readDouble();
        final double southY = in.readDouble();
        final double westX = in.readDouble();
        return new WayPointBounds(northY, eastX, southY, westX);
    }

    /**
     * Builder for composing WayPointBounds objects.
     */
    public static final class Builder {

        private final List<WayPoint> wayPointList = new ArrayList<>();

        /**
         * Builds a new WayPointBounds.
         * <p>
         * Throws an {@link InvalidWayPointBoundsException} when no WayPointBounds can be created.
         * </p>
         *
         * @return the build WayPointBounds
         */
        public WayPointBounds build() {
            if (wayPointList.size() < 2) {
                throw new InvalidWayPointBoundsException(wayPointList.size());
            }
            return WayPointBounds.fromWayPoints(wayPointList);
        }


        @NonNull
        public Builder includes(@NonNull List<WayPoint> wayPoints) {
            wayPointList.addAll(wayPoints);
            return this;
        }


        @NonNull
        public Builder include(@NonNull WayPoint wayPoint) {
            wayPointList.add(wayPoint);
            return this;
        }
    }
}
