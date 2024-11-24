//
// Created by gongxi on 2024/9/2.
//
#include <algorithm>
#include "transform_state.h"
#include "utils/log.h"
#include "utils/geometry.h"
#include "utils/tile_coordinate.h"
#include "utils/interpolate.h"

namespace roamgl
{



TransformState::TransformState()  {


}

TransformState::~TransformState() {

}

float TransformState::getBearing() const
{
    return mBearing;
}

float TransformState::getFieldOfView() const
{
    return mFov;
}


float TransformState::getPitch() const
{
    return mPitch;
}

float TransformState::getCameraToCenterDistance() const
{
    return 0.5 * mSize.height / std::tan(mFov / 2.0);
}

ScreenCoordinate TransformState::getCenterOffset() const
{
    return { 0.5 * (mEdgeInsets.left() - mEdgeInsets.right()), 0.5 * (mEdgeInsets.top() - mEdgeInsets.bottom()) };
}

void TransformState::constrain(double& scale_, double& x_, double& y_) const
{
    const double ratioY = mSize.height / util::tileSize;
    scale_ = std::max(scale_, ratioY);

    // 缩放时避免Y方向越界
//    double max_y = (scale_ * util::tileSize - mSize.height) / 2;
//    y_ = std::max(-max_y, std::min(y_, max_y));
}




Size TransformState::getSize() const
{
    return mSize;
}

void TransformState::moveWayPoint(const WayPoint& wayPoint, const ScreenCoordinate& anchor)
{
    auto centerCoord = Projection::project(getWayPoint(), mScale);
    auto latLngCoord = Projection::project(wayPoint, mScale);
    auto anchorCoord = Projection::project(screenCoordinateToWayPoint(anchor), mScale);

    roamgl::Log::Info(roamgl::Event::Render, "NativeRoamView moveWayPoint "
                                             "[%.5f %.5f]  [%.5f %.5f]  [%.5f %.5f] ",
                                             getWayPoint().getX(), getWayPoint().getY(),
                                             wayPoint.getX(), wayPoint.getY(),
                                             screenCoordinateToWayPoint(anchor).getX(), screenCoordinateToWayPoint(anchor).getY());

    setWayPointZoom(Projection::unproject(centerCoord + latLngCoord - anchorCoord, mScale), getZoom());
}

WayPoint TransformState::getWayPoint() const {
    roamgl::Log::Info(roamgl::Event::Render, "getWayPoint [%.5f %.5f] ", mX / Bc, mY / Cc);
    return {-mX / Bc , mY / Cc};
}


void TransformState::setWayPointZoom(const WayPoint& wayPoint, double zoom)
{
    roamgl::Log::Info(roamgl::Event::Render, "NativeRoamView setWayPointZoom "
                                             "[%.5f %.5f %.5f] ", wayPoint.getX(), wayPoint.getY(), zoom);
    WayPoint constrained = wayPoint;
    constrained = mBounds.constrain(wayPoint);

    double newScale = std::clamp(zoomScale(zoom), min_scale, max_scale);
    const double newWorldSize = newScale * util::tileSize;
    Bc = newWorldSize / util::WAY_POINT_DISTANCE_MAX;
    Cc = newWorldSize / util::WAY_POINT_DISTANCE_MAX;

    ScreenCoordinate point = {
            -Bc * constrained.getX(),
             Cc * constrained.getY(),
    };

    setScalePoint(newScale, point);
}

void TransformState::setScalePoint(const double newScale, const ScreenCoordinate& point)
{
    double constrainedScale = newScale;
    ScreenCoordinate constrainedPoint = point;
    constrain(constrainedScale, constrainedPoint.x, constrainedPoint.y);

    mScale = constrainedScale;
    mX = constrainedPoint.x;
    mY = constrainedPoint.y;
    Bc = Projection::worldSize(mScale) / util::WAY_POINT_DISTANCE_MAX;
    Cc = Projection::worldSize(mScale) / util::WAY_POINT_DISTANCE_MAX;

    roamgl::Log::Info(roamgl::Event::Render, "NativeRoamView setScalePoint "
                                             "[%.5f %.5f] [%.5f %.5f %.5f] ", point.x, point.y, mX, mY, mScale);
}


CameraOptions TransformState::getCameraOptions(const EdgeInsets &padding) const {
    return CameraOptions()
            .withCenter(getWayPoint())
            .withPadding(padding)
            .withZoom(getZoom())
            .withBearing(-mBearing * util::RAD2DEG)
            .withPitch(mPitch * util::RAD2DEG);
}


double TransformState::zoomScale(double zoom) const
{
    return std::pow(2.0, zoom);
}
double TransformState::scaleZoom(double scale) const
{
    return std::log2(scale);
}

double TransformState::getZoom() const {
    return scaleZoom(mScale);
}

double TransformState::getScale() const {
    return mScale;
}

void TransformState::setWayPointBounds(WayPointBounds bounds_)
{
    if (bounds_ != mBounds) {
        mBounds = bounds_;
        setWayPointZoom(getWayPoint(), getZoom());
    }
}

WayPointBounds TransformState::getWayPointBounds() const
{
    return mBounds;
}


void TransformState::setMinZoom(const double minZoom) {
    if (minZoom <= getMaxZoom()) {
        min_scale = zoomScale(std::clamp(minZoom, util::MIN_ZOOM, util::MAX_ZOOM));
    }
}

double TransformState::getMinZoom() const
{
    double curScale = min_scale;
    double unused_x = mX;
    double unused_y = mY;
    constrain(curScale, unused_x, unused_y);

    return scaleZoom(curScale);
}

void TransformState::setMaxZoom(const double maxZoom)
{
    if (maxZoom >= getMinZoom()) {
        max_scale = zoomScale(std::clamp(maxZoom, util::MIN_ZOOM, util::MAX_ZOOM));
    }
}

double TransformState::getMaxZoom() const
{
    return scaleZoom(max_scale);
}


TileCoordinate TransformState::screenCoordinateToTileCoordinate(const ScreenCoordinate& point, uint8_t atZoom) const
{
    if (mSize.isEmpty()) {
        return { };
    }

    float targetZ = 0;
    glm::mat4 mat = coordinatePointMatrix();

    glm::mat4 inverted = glm::inverse(mat);
    double flippedY = mSize.height - point.y;

    glm::vec4 point0 { point.x, flippedY, 0, 1 };
    glm::vec4 point1 { point.x, flippedY, 1, 1 };
    glm::vec4 coord0 = inverted * point0;
    glm::vec4 coord1 = inverted * point1;

    double w0 = coord0[3];
    double w1 = coord1[3];

    Point<double> p0 = Point<double>(coord0[0], coord0[1]) / w0;
    Point<double> p1 = Point<double>(coord1[0], coord1[1]) / w1;

    double z0 = coord0[2] / w0;
    double z1 = coord1[2] / w1;
    double t = z0 == z1 ? 0 : (targetZ - z0) / (z1 - z0);

    Point<double> p = util::interpolate(p0, p1, t) / mScale * static_cast<double>(1 << atZoom);

    roamgl::Log::Info(roamgl::Event::Render, "screenCoordinateToTileCoordinate "
                                             "[%.5f %.5f %.5f] [%.5f %.5f] [%.10f %.10f][%.5f]", point.x, point.y, flippedY,
                      coord0.x, coord0.y, p.x, p.y, mScale);

    return {{p.x, p.y} };
}

ScreenCoordinate TransformState::wayPointToScreenCoordinate(const WayPoint& wayPoint) const
{
    if (mSize.isEmpty()) {
        return {};
    }
    glm::mat4 mat = coordinatePointMatrix();

    Point<double> pt = Projection::project(wayPoint, mScale) / util::tileSize;

    glm::vec4 pos {pt.x, pt.y, 0.0, 1.0};

    pos = mat * pos;

    return { pos[0] / pos[3], mSize.height - pos[1] / pos[3] };
}

WayPoint TransformState::screenCoordinateToWayPoint(const ScreenCoordinate& point) const
{
    auto coord = screenCoordinateToTileCoordinate(point, 0);
    return Projection::unproject(coord.p, 1 / util::tileSize);
}

glm::mat4 TransformState::coordinatePointMatrix() const
{
    glm::mat4 proj{1.0f};
    getProjMatrix(proj);
    proj = glm::scale(proj, glm::vec3 {util::tileSize,  util::tileSize, 1});
    proj = getPixelMatrix() * proj;
    return proj;
}

/**
 * NDC坐标归一化
 * @return
 */
glm::mat4 TransformState::getPixelMatrix() const
{
    glm::mat4 pixelMat{1.0f};
    pixelMat = glm::scale(pixelMat, glm::vec3 {static_cast<double>(mSize.width) / 2, -static_cast<double>(mSize.height) / 2 , 1});
    pixelMat = glm::translate(pixelMat, glm::vec3 {1, -1, 0});
    return pixelMat;
}

void TransformState::getProjMatrix(glm::mat4& matrix) const
{
    if (mSize.isEmpty()) {
        return;
    }

    const double cameraToCenterDistance = getCameraToCenterDistance();
    auto offset = getCenterOffset();
    // See https://github.com/mapbox/mapbox-gl-native/pull/15195 for details.
    // See TransformState::fov description: fov = 2 * arctan((height / 2) / (height * 1.5)).
    const double tanFovAboveCenter = (mSize.height * 0.5 + offset.y) / (mSize.height * 1.5);
    const double tanMultiple = tanFovAboveCenter * std::tan(getPitch());

    assert(tanMultiple < 1);
    const double furthestDistance = cameraToCenterDistance / (1 - tanMultiple);
    float farZ = furthestDistance * 1.01;

    matrix = glm::perspective(getFieldOfView(), float(mSize.width) / mSize.height, 1.0f, farZ) ;
    matrix = glm::scale(matrix, glm::vec3(1.0, -1.0, 1.0));

    matrix = glm::translate(matrix, glm::vec3 {0, 0, -cameraToCenterDistance});

    matrix = glm::rotate(matrix, static_cast<float>(getPitch()), glm::vec3 (1.0f, 0.0f, 0.0f));
    matrix = glm::rotate(matrix, static_cast<float>(getBearing()), glm::vec3(0.0f, 0.0f, 1.0f));
    // [0, 0] 为原点 到[1, 1] ===》[0, 0] [256, 256]
    const double dx = pixel_x() - mSize.width / 2.0f, dy = pixel_y() - mSize.height / 2.0f;
    matrix = glm::translate(matrix, glm::vec3 {dx, dy, 0});

    roamgl::Log::Info(roamgl::Event::Render, "getProjMatrix [%.5f %.5f][%.5f %.5f] ", mX, mY, dx, dy);
}

double TransformState::pixel_x() const
{
    const double center = (mSize.width - Projection::worldSize(mScale)) / 2;
    return center + mX;
}

double TransformState::pixel_y() const
{
    const double center = (mSize.height - Projection::worldSize(mScale)) / 2;
    return center + mY;
}

}



