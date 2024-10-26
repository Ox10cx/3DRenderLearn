//
// Created by gongxi on 2024/9/2.
//

#include "transform.h"
#include "utils/log.h"
#include "utils/constants.h"
#include "utils/wrap.h"


namespace roamgl
{

static double _normalizeAngle(double angle, double anchorAngle)
{
    if (std::isnan(angle) || std::isnan(anchorAngle)) {
        return 0;
    }

    angle = util::wrap(angle, -M_PI, M_PI);
    if (angle == -M_PI) angle = M_PI;
    double diff = std::abs(angle - anchorAngle);
    if (std::abs(angle - util::M2PI - anchorAngle) < diff) {
        angle -= util::M2PI;
    }
    if (std::abs(angle + util::M2PI - anchorAngle) < diff) {
        angle += util::M2PI;
    }

    return angle;
}

Transform::Transform()
        : mState() {

}

Transform::~Transform() {

}

void Transform::resize(const Size size)
{
    if (size.isEmpty()) {
        throw std::runtime_error("failed to resize: size is empty");
    }

    if (mState.mSize == size) {
        return;
    }

    mState.mSize = size;

    mState.constrain(mState.mScale, mState.mX, mState.mY);

}

void Transform::moveBy(const ScreenCoordinate &offset) {
    ScreenCoordinate centerOffset = { offset.x, offset.y };
    ScreenCoordinate pointOnScreen = mState.mEdgeInsets.getCenter(mState.mSize.width, mState.mSize.height) - centerOffset;
    easeTo(CameraOptions().withCenter(screenCoordinateToWayPoint(pointOnScreen)));
}

void Transform::easeTo(const CameraOptions &camera) {
    WayPoint startWayPoint = getWayPoint();
    WayPoint endWayPoint = camera.center.value_or(startWayPoint);

    double bearing = camera.bearing ? -*camera.bearing * util::DEG2RAD : getBearing();
    double pitch = camera.pitch ? *camera.pitch * util::DEG2RAD : getPitch();

    if (std::isnan(bearing) || std::isnan(pitch)) {
        return;
    }

    pitch = std::clamp(pitch, util::PITCH_MIN, util::PITCH_MAX);

    bearing = _normalizeAngle(bearing, mState.mBearing);
    mState.mBearing = _normalizeAngle(mState.mBearing, bearing);

    // 先换算
    std::optional<ScreenCoordinate> anchor = camera.center ? std::nullopt : camera.anchor;
    WayPoint anchorWayPoint;
    if (anchor) {
        anchor->y = mState.mSize.height - anchor->y;
        anchorWayPoint = mState.screenCoordinateToWayPoint(*anchor);
    }

    mState.setWayPointZoom(endWayPoint, 0.0f);

    if (mState.mBearing != bearing) {
        mState.mBearing = bearing;
    }

    if (mState.mPitch != pitch) {
        mState.mPitch = pitch;
    }

    if (anchor) mState.moveWayPoint(anchorWayPoint, *anchor);
}

double Transform::getBearing() const
{
    return mState.mBearing;
}

double Transform::getPitch() const
{
    return mState.mPitch;
}

CameraOptions Transform::getCameraOptions(const EdgeInsets& padding) const {
    return mState.getCameraOptions(padding);
}


WayPoint Transform::screenCoordinateToWayPoint(const ScreenCoordinate& point) const {
    ScreenCoordinate flippedPoint = point;
    flippedPoint.y = mState.mSize.height - flippedPoint.y;
    return mState.screenCoordinateToWayPoint(flippedPoint);
}


WayPoint Transform::getWayPoint() const
{
    return mState.getWayPoint();
}

}



