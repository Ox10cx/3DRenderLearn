//
// Created by gongxi on 2024/8/30.
//

#include "android_renderer_frontend.h"

AndroidRendererFrontend::AndroidRendererFrontend(RoamRenderer &roamRender_)
        : roamRenderer(roamRender_) {


}

AndroidRendererFrontend::~AndroidRendererFrontend() = default;


void AndroidRendererFrontend::update(std::shared_ptr<roamgl::UpdateParameters> params)
{
    roamRenderer.update(std::move(params));
    roamRenderer.requestRender();
}
