package com.gx.kotlin.scene.camera;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;

import com.gx.kotlin.scene.roam.DriveRoam;

public interface CameraUpdate {

    @Nullable
    CameraPosition getCameraPosition(@NonNull DriveRoam driveRoam);

}