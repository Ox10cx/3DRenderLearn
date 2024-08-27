package com.gx.kotlin.scene.roam.render;

public interface RoamRendererScheduler {
    void requestRender();

    void queueEvent(Runnable runnable);
}
