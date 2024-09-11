//
// Created by gongxi on 2024/8/30.
//

#ifndef ASSIMPDEMO_ANDROID_RENDERER_FRONTEND_H
#define ASSIMPDEMO_ANDROID_RENDERER_FRONTEND_H

#include "renderer/renderer_frontend.h"
#include "roam_renderer.h"

class AndroidRendererFrontend : public roamgl::RendererFrontend {
public:
    AndroidRendererFrontend(RoamRenderer&);
    ~AndroidRendererFrontend() override;

    void update(std::shared_ptr<roamgl::UpdateParameters>) override;

private:
    RoamRenderer& roamRenderer;
};


#endif //ASSIMPDEMO_ANDROID_RENDERER_FRONTEND_H
