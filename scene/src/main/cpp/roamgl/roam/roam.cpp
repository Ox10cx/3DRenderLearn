//
// Created by gongxi on 2024/8/30.
//
#include "renderer/renderer_frontend.h"
#include "roam_impl.h"
#include "roam.h"

namespace roamgl
{

    Roam::Roam(RendererFrontend &frontend,
               const RoamOptions& options)
            : mImpl(std::make_unique<Impl>(frontend, options)) {

    }

    Roam::~Roam() = default;

    void Roam::setSize(const Size size) {
        mImpl->mTransForm.resize(size);
        mImpl->onUpdate();
    }

    void Roam::moveBy(const roamgl::ScreenCoordinate& point)
    {
        mImpl->mTransForm.moveBy(point);
        mImpl->onUpdate();
    }

    void Roam::easeTo(const roamgl::CameraOptions& camera)
    {
        mImpl->mTransForm.easeTo(camera);
        mImpl->onUpdate();
    }


    roamgl::CameraOptions Roam::getCameraOptions(const roamgl::EdgeInsets& padding)
    {
        return mImpl->mTransForm.getCameraOptions(padding);
    }

}


