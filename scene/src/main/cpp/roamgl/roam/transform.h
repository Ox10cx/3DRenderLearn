//
// Created by gongxi on 2024/9/2.
//

#ifndef ASSIMPDEMO_TRANSFORM_H
#define ASSIMPDEMO_TRANSFORM_H

#include "geo.h"
#include "camera.h"
#include "transform_state.h"

namespace roamgl {

class Transform {

public:
    Transform();

    Transform(const TransformState &state_) :  mState(state_) {}

    ~Transform();

    void resize(const Size size);

    void moveBy(const ScreenCoordinate &offset);

    void easeTo(const CameraOptions&, const AnimationOptions& = {});

    const TransformState &getState() const { return mState; }

    CameraOptions getCameraOptions(const EdgeInsets&) const;
    void jumpTo(const CameraOptions&);

    double getBearing() const;

    double getPitch() const;

    void setWayPointBounds(WayPointBounds);
    void setMinZoom(double);
    void setMaxZoom(double);

    double getZoom() const;

    WayPoint screenCoordinateToWayPoint(const ScreenCoordinate& point) const;

    ScreenCoordinate wayPointToScreenCoordinate(const WayPoint& wayPoint) const;

    WayPoint getWayPoint() const;

private:
    TransformState mState;


};

}


#endif //ASSIMPDEMO_TRANSFORM_H
