//
// Created by gongxi on 2024/8/30.
//

#ifndef ASSIMPDEMO_ROAM_IMPL_H
#define ASSIMPDEMO_ROAM_IMPL_H
#include "roam.h"
#include "renderer/renderer_frontend.h"
#include "roam/transform.h"
#include "roam_options.h"

namespace roamgl
{

class Roam::Impl {
public:
    Impl(RendererFrontend&, const RoamOptions&);
    ~Impl();

    void onUpdate();

public:
    RendererFrontend& mRendererFrontend;
    Transform mTransForm;

    const float mPixelRatio;

};

}



#endif //ASSIMPDEMO_ROAM_IMPL_H
