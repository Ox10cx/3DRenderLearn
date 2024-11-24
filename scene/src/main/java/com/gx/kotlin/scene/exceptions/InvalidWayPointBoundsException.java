package com.gx.kotlin.scene.exceptions;

public class InvalidWayPointBoundsException extends RuntimeException {

    public InvalidWayPointBoundsException(int wayPointListSize) {
        super("Cannot create a WayPointBounds from " + wayPointListSize + " items");
    }
}