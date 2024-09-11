//
// Created by gongxi on 2024/9/2.
//

#ifndef ASSIMPDEMO_ROAM_OPTIONS_H
#define ASSIMPDEMO_ROAM_OPTIONS_H

#include <memory>
#include "utils/size.h"

namespace roamgl
{

class RoamOptions final {
public:
    RoamOptions();

    ~RoamOptions();

    RoamOptions(RoamOptions &&) noexcept;

    RoamOptions &withSize(Size size_);

    Size size() const;

    RoamOptions &withPixelRatio(float ratio);

    float pixelRatio() const;


private:
    class Impl;

    std::unique_ptr<Impl> mImpl;
};

}


#endif //ASSIMPDEMO_ROAM_OPTIONS_H
