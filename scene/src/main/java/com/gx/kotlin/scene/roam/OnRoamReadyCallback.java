package com.gx.kotlin.scene.roam;

import androidx.annotation.NonNull;

public interface OnRoamReadyCallback {
    void onMapReady(@NonNull DriveRoam driveRoam);
}
