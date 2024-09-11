//
// Created by gongxi on 2024/9/2.
//

#include "roam_options.h"

namespace roamgl
{

class RoamOptions::Impl {
public:
    Size size {64, 64};
    float pixelRatio = 1.0;
};

RoamOptions::RoamOptions() : mImpl(std::make_unique<Impl>()){}
RoamOptions::~RoamOptions() = default;
RoamOptions::RoamOptions(RoamOptions&&) noexcept = default;


RoamOptions& RoamOptions::withSize(Size size_)
{
    mImpl->size = size_;
    return *this;
}


Size RoamOptions::size() const
{
    return mImpl->size;
}


RoamOptions& RoamOptions::withPixelRatio(float ratio)
{
    mImpl->pixelRatio = ratio;
    return *this;
}

float RoamOptions::pixelRatio() const
{
    return mImpl->pixelRatio;
}


}
