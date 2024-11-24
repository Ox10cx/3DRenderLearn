//
// Created by gongxi on 2024/8/30.
//

#ifndef ASSIMPDEMO_ROAM_H
#define ASSIMPDEMO_ROAM_H
#include <memory>
#include <optional>

#include "utils/geo.h"
#include "roam/roam_options.h"
#include "roam/bound_options.h"
#include "roam/camera.h"
#include "transform.h"

namespace roamgl
{

class RendererFrontend;

class Roam {
public:
    explicit Roam(RendererFrontend &, const RoamOptions &);

    ~Roam();

    void setSize(const Size);

    void moveBy(const roamgl::ScreenCoordinate &);

    void jumpTo(const CameraOptions&);
    void easeTo(const roamgl::CameraOptions&, const AnimationOptions&);

    CameraOptions getCameraOptions(const EdgeInsets& = {}) const;

    void setBounds(const BoundOptions& options);

    BoundOptions getBounds() const;

    ScreenCoordinate pixelForWayPoint(const WayPoint&) const;
    WayPoint wayPointForPixel(const ScreenCoordinate&) const;

    CameraOptions cameraForWayPointBounds(const WayPointBounds&, const EdgeInsets&, std::optional<double> bearing = {}, std::optional<double> pitch = {}) const;
    CameraOptions cameraForWayPoints(const std::vector<WayPoint>&, const EdgeInsets&, std::optional<double> bearing = {}, std::optional<double> pitch = {}) const;




protected:
    class Impl;

    const std::unique_ptr<Impl> mImpl;


};

}


#endif //ASSIMPDEMO_ROAM_H
