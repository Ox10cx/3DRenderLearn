//
// Created by gongxi on 2024/8/30.
//

#ifndef ASSIMPDEMO_ROAM_H
#define ASSIMPDEMO_ROAM_H
#include <memory>
#include "utils/geo.h"
#include "roam/roam_options.h"
#include "roam/camera.h"

namespace roamgl
{

class RendererFrontend;

class Roam {
public:
    explicit Roam(RendererFrontend &, const RoamOptions &);

    ~Roam();

    void setSize(const Size);

    void moveBy(const roamgl::ScreenCoordinate &);

    void easeTo(const roamgl::CameraOptions &);

    roamgl::CameraOptions getCameraOptions(const roamgl::EdgeInsets &padding);


protected:
    class Impl;

    const std::unique_ptr<Impl> mImpl;

};

}


#endif //ASSIMPDEMO_ROAM_H
