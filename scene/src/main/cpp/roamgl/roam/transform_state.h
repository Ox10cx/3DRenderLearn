//
// Created by gongxi on 2024/9/2.
//

#ifndef ASSIMPDEMO_TRANSFORM_STATE_H
#define ASSIMPDEMO_TRANSFORM_STATE_H

#include "glm/glm_core.h"
#include "utils/size.h"
#include "utils/geo.h"
#include "utils/constants.h"
#include "utils/projection.h"
#include "camera.h"

namespace roamgl
{


class TileCoordinate;

class TransformState {
    friend class Transform;

public:
    TransformState();

    ~TransformState();

    Size getSize() const;

    glm::mat4 getProjMatrix() const;

    glm::mat4 coordinatePointMatrix() const;

    glm::mat4 getPixelMatrix() const;

    void getTransMatrix(glm::mat4& matrix) const;

    CameraOptions getCameraOptions(const EdgeInsets& padding) const;

    WayPoint getWayPoint() const;

    double pixel_x() const;
    double pixel_y() const;

    double getZoom() const;
    float getBearing() const;
    float getFieldOfView() const;
    float getCameraToCenterDistance() const;
    float getPitch() const;

    double zoomScale(double zoom) const;
    double scaleZoom(double scale) const;

    void setPitch(double pitch);

    void setWayPointZoom(const WayPoint& wayPoint, double zoom);
    void setScalePoint(const double scale, const ScreenCoordinate& point);


    WayPoint screenCoordinateToWayPoint(const ScreenCoordinate& point) const;

    TileCoordinate screenCoordinateToTileCoordinate(const ScreenCoordinate& point, uint8_t atZoom) const;

    ScreenCoordinate wayPointToScreenCoordinate(const WayPoint& wayPoint) const;

    void moveWayPoint(const WayPoint& wayPoint, const ScreenCoordinate& anchor);

private:
    void constrain(double& scale, double& x, double& y) const;

    ScreenCoordinate getCenterOffset() const;

private:
    double mX{0.0};
    double mY{0.0};
    double mBearing {0.0};
    double mScale {1.0};
    // `fov = 2 * arctan((height / 2) / (height * 1.5))`
    double mFov = 0.6435011087932844;
    double mPitch{0.0f};

    Size mSize;

    roamgl::EdgeInsets mEdgeInsets;


    double minScale = std::pow(2, 0);
    double maxScale = std::pow(2, util::DEFAULT_MAX_ZOOM);

    double Bc = Projection::worldSize(mScale);
    double Cc = Projection::worldSize(mScale) ;
};


}



#endif //ASSIMPDEMO_TRANSFORM_STATE_H
