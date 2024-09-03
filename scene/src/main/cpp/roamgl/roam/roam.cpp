//
// Created by gongxi on 2024/8/30.
//
#include "renderer/renderer_frontend.h"
#include "roam_impl.h"
#include "roam.h"

Roam::Roam(RendererFrontend &frontend,
           const RoamOptions& options)
        : mImpl(std::make_unique<Impl>(frontend, options)) {

}

void Roam::setSize(const Size size) {
    mImpl->mTransForm.resize(size);
    mImpl->onUpdate();
}

void Roam::moveBy(const ScreenCoordinate& point)
{
    mImpl->mTransForm.moveBy(point);
    mImpl->onUpdate();
}

Roam::~Roam() = default;
