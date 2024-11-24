package com.gx.kotlin.scene.geometry;

import android.os.Parcel;
import android.os.Parcelable;

import androidx.annotation.NonNull;

public class WayPointSpan implements Parcelable {
    private double mXSpan;
    private double mYSpan;

    private WayPointSpan(@NonNull Parcel in) {
        mXSpan = in.readDouble();
        mYSpan = in.readDouble();
    }


    public WayPointSpan(double xSpan, double ySpan) {
        mXSpan = xSpan;
        mYSpan = ySpan;
    }


    public double getYSpan() {
        return mYSpan;
    }

    public void setYSpan(double ySpan) {
        mYSpan = ySpan;
    }

    public double getXSpan() {
        return mXSpan;
    }

    public void setXSpan(double xSpan) {
        mXSpan = xSpan;
    }


    @Override
    public boolean equals(Object object) {
        if (this == object) {
            return true;
        }
        if (object instanceof WayPointSpan) {
            WayPointSpan other = (WayPointSpan) object;
            return mXSpan == other.getXSpan()
                    && mYSpan == other.getYSpan();
        }
        return false;
    }


    public static final Parcelable.Creator<WayPointSpan> CREATOR =
            new Parcelable.Creator<WayPointSpan>() {
                @Override
                public WayPointSpan createFromParcel(@NonNull Parcel in) {
                    return new WayPointSpan(in);
                }

                @Override
                public WayPointSpan[] newArray(int size) {
                    return new WayPointSpan[size];
                }
            };


    @Override
    public int describeContents() {
        return 0;
    }


    @Override
    public void writeToParcel(@NonNull Parcel out, int flags) {
        out.writeDouble(mYSpan);
        out.writeDouble(mXSpan);
    }


    @Override
    public int hashCode() {
        int result;
        long temp;
        temp = Double.doubleToLongBits(mYSpan);
        result = (int) (temp ^ (temp >>> 32));
        temp = Double.doubleToLongBits(mXSpan);
        result = 31 * result + (int) (temp ^ (temp >>> 32));
        return result;
    }

}
