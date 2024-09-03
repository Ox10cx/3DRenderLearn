//
// Created by gongxi on 2024/9/2.
//

#include "transform.h"
#include "utils/log.h"

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
    //todo 这里重新计算中心点
}

void Transform::moveBy(const ScreenCoordinate &offset) {
    ScreenCoordinate centerOffset = { offset.x, offset.y };
    ScreenCoordinate pointOnScreen = mState.mEdgeInsets.getCenter(mState.mSize.width, mState.mSize.height) - centerOffset;
    earseTo(CameraOptions().withCenter(pointOnScreen));
}

void Transform::earseTo(const CameraOptions &camera) {
    ScreenCoordinate defaultCoordinate = mState.mEdgeInsets.getCenter(mState.mSize.width, mState.mSize.height);
    const ScreenCoordinate& centerCoordinate = camera.center.value_or(defaultCoordinate);
    mState.setScreenCoordinate(centerCoordinate, 0.0f);
}

