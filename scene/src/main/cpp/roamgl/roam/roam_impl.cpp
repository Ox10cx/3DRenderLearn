//
// Created by gongxi on 2024/8/30.
//

#include "roam_impl.h"
#include "renderer/update_parameters.h"

namespace roamgl
{

Roam::Impl::Impl(RendererFrontend &frontend_,
                 const RoamOptions &roamOptions)
        : mRendererFrontend(frontend_),
          mTransForm(),
          mPixelRatio(roamOptions.pixelRatio()) {
    mTransForm.resize(roamOptions.size());
}

Roam::Impl::~Impl() {

}


void Roam::Impl::onUpdate() {
    UpdateParameters params = {
            mTransForm.getState()
    };
    mRendererFrontend.update(std::make_shared<UpdateParameters>(std::move(params)));
}

}
