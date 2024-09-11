//
// Created by gongxi on 2024/9/2.
//

#ifndef ASSIMPDEMO_TRANSFORM_STATE_H
#define ASSIMPDEMO_TRANSFORM_STATE_H

#include "glm/glm_core.h"
#include "utils/size.h"
#include "utils/geo.h"
#include "camera.h"

namespace roamgl
{

class TransformState {
    friend class Transform;

public:
    TransformState();

    ~TransformState();

    Size getSize() const;

    glm::mat4 getProjMatrix() const;

    CameraOptions getCameraOptions(const EdgeInsets& padding) const;

    WayPoint getWayPoint() const;

    double getZoom() const;

public:

    void setBearingXY(const ScreenCoordinate &anchor, double bearing);

    void setBearingXY(double bearing);

    void setPitch(double pitch);

    void setWayPointZoom(const WayPoint& wayPoint, double zoom);

    WayPoint screenCoordinateToWayPoint(const ScreenCoordinate& point) const;

    void moveWayPoint(const WayPoint& wayPoint, const ScreenCoordinate& anchor);


private:
    double mX{0.0};
    double mY{0.0};
    double mBearing{0.0};
    double mScale{1.0};
    double mFov{45.0f};
    double mPitch{0.0f};

    Size mSize;

    roamgl::EdgeInsets mEdgeInsets;

    glm::vec3 mPosition{0.0f, 0.0f, 1.0f};
    glm::vec3 mUp{0.0f, 1.0f, 0.0f};
    glm::vec3 mRight{1.0f, 0.0f, 0.0f};
};


}



#endif //ASSIMPDEMO_TRANSFORM_STATE_H
