package com.gx.kotlin.scene.geometry;

import android.os.Parcel;
import android.os.Parcelable;

import androidx.annotation.Keep;
import androidx.annotation.NonNull;
import androidx.annotation.Nullable;

public class WayPoint implements Parcelable {

    public static final Parcelable.Creator<WayPoint> CREATOR = new Parcelable.Creator<WayPoint>() {
        public WayPoint createFromParcel(@NonNull Parcel in) {
            return new WayPoint(in);
        }

        public WayPoint[] newArray(int size) {
            return new WayPoint[size];
        }
    };

    @Keep
    private double x;
    @Keep
    private double y;
    private double z = 0.0;

    public WayPoint() {
        this.x = 0.0;
        this.y = 0.0;
    }

    @Keep
    public WayPoint(double x, double y) {
        setX(x);
        setY(y);
    }


    public WayPoint(double x, double y, double z) {
        setX(x);
        setY(y);
        setZ(z);
    }


    public WayPoint(WayPoint point) {
        this.x = point.x;
        this.y = point.y;
        this.z = point.z;
    }

    /**
     * Constructs a new latitude, longitude, altitude tuple given a parcel.
     *
     * @param in the parcel containing the latitude, longitude, altitude values
     */
    protected WayPoint(Parcel in) {
        setX(in.readDouble());
        setY(in.readDouble());
        setZ(in.readDouble());
    }


    public void setX(double x) {
        this.x = x;
    }


    public double getX() {
        return x;
    }


    public void setY(double y) {
        this.y = y;
    }


    public double getY() {
        return y;
    }


    public void setZ(double z) {
        this.z = z;
    }


    public double getZ() {
        return z;
    }



    @Override
    public boolean equals(@Nullable Object object) {
        if (this == object) {
            return true;
        }
        if (object == null || getClass() != object.getClass()) {
            return false;
        }

        WayPoint point = (WayPoint) object;

        return Double.compare(point.z, z) == 0 && Double.compare(point.x, x) == 0
                && Double.compare(point.y, y) == 0;
    }

    /**
     * Returns a hash code value for the object.
     *
     * @return the hash code value
     */
    @Override
    public int hashCode() {
        int result;
        long temp;
        temp = Double.doubleToLongBits(x);
        result = (int) (temp ^ (temp >>> 32));
        temp = Double.doubleToLongBits(y);
        result = 31 * result + (int) (temp ^ (temp >>> 32));
        temp = Double.doubleToLongBits(z);
        result = 31 * result + (int) (temp ^ (temp >>> 32));
        return result;
    }


    @NonNull
    @Override
    public String toString() {
        return "WayPoint [x=" + x + ", y=" + y + ", z=" + z + "]";
    }


    @Override
    public int describeContents() {
        return 0;
    }


    @Override
    public void writeToParcel(@NonNull Parcel out, int flags) {
        out.writeDouble(x);
        out.writeDouble(y);
        out.writeDouble(z);
    }

}
