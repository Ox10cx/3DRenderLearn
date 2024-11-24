package com.gx.kotlin.scene.roam.renderer;

public interface RoamRendererScheduler {
    void requestRender();

    void queueEvent(Runnable runnable);
}
