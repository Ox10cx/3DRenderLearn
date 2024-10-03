//
// Created by gongxi on 2024/9/2.
//

#include "transform.h"
#include "utils/log.h"
#include "utils/constants.h"


namespace roamgl
{

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
    mState.setWayPointZoom(endWayPoint, 0.0f);

//    // 先换算
//    std::optional<ScreenCoordinate> anchor = camera.center ? std::nullopt : camera.anchor;
//    WayPoint anchorWayPoint;
//    if (anchor) {
//        anchor->y = mState.mSize.height - anchor->y;
//        anchorWayPoint = mState.screenCoordinateToWayPoint(*anchor);
//    }
//
//    double bearing = camera.bearing ? -*camera.bearing * util::DEG2RAD : getBearing();
//    if (mState.mBearing != bearing) {
//        mState.mBearing = bearing;
//        mState.setBearingXY(bearing);
//    }
//
//    if (anchor) mState.moveWayPoint(anchorWayPoint, *anchor);

//    const roamgl::ScreenCoordinate& anchor = camera.anchor.value_or(defaultCoordinate);
//    mState.setBearingXY(anchor, bearing);


//    const ScreenCoordinate defaultCoordinate = mState.mEdgeInsets.getCenter(mState.mSize.width, mState.mSize.height);
//    const ScreenCoordinate& centerCoordinate = camera.center.value_or(defaultCoordinate);
//    mState.setScreenCoordinate(centerCoordinate, 0.0f);
//
//    double pitch = camera.pitch ? *camera.pitch * util::DEG2RAD : getPitch();
//    mState.mPitch = pitch;
//    mState.setPitch(pitch);
//
//
//    double bearing = camera.bearing ? -*camera.bearing * util::DEG2RAD : getBearing();
//    mState.mBearing = bearing;
//    const roamgl::ScreenCoordinate& anchor = camera.anchor.value_or(defaultCoordinate);
//    mState.setBearingXY(anchor, bearing);
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



