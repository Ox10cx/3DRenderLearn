//
// Created by gongxi on 2024/9/2.
//

#include "transform_state.h"
#include "utils/constants.h"
#include "utils/log.h"

namespace roamgl
{


TransformState::TransformState() {

}

TransformState::~TransformState() {

}

glm::mat4 TransformState::getProjMatrix() const
{
//    float offsetX = (mX + mSize.width / 2.0)  * 2 - mSize.width;
//    float offsetY = (mY + mSize.height/ 2.0)  * 2 - mSize.height;
//    float dx = offsetX / mSize.width;
//    float dy = offsetY / mSize.height;
//
//    roamgl::Log::Info(roamgl::Event::Render, "NativeRoamView getProjMatrix %.2f %.2f ", dx, dy);
//
//
//    auto up = glm::normalize(mUp);
//    auto right = glm::normalize(mRight);
//    glm::vec3 direction(0.0f);
//    direction += mUp * dy;
//    direction += mRight * dx;
//    roamgl::Log::Info(roamgl::Event::Render, "NativeRoamView direction %.2f %.2f %.2f ", direction.x, direction.y, direction.z);

    glm::vec3 front = glm::cross(mUp, mRight);
    glm::vec3 center = front + mPosition;
    return glm::lookAt(mPosition, center, mUp);
}


Size TransformState::getSize() const
{
    return mSize;
}

void TransformState::moveWayPoint(const WayPoint& wayPoint, const ScreenCoordinate& anchor)
{
    auto centerCoord = getWayPoint();
    auto anchorCoord = screenCoordinateToWayPoint(anchor);

    WayPoint point {centerCoord.getX() +  mSize.width / 4.0,
                    centerCoord.getY()};

    setWayPointZoom(point, getZoom());
}

void TransformState::setWayPointZoom(const WayPoint& wayPoint, double zoom)
{
    glm::vec4 offsetPos{wayPoint.getX(), wayPoint.getY(), 0.0, 1.0};

    glm::mat4 transform{1.0f};
    transform = glm::scale(transform, glm::vec3 {static_cast<double>(mSize.width) / 2, -static_cast<double>(mSize.height) / 2 , 1});
    transform = glm::translate(transform, glm::vec3 {1, -1, 0});
    offsetPos = glm::inverse(transform) * offsetPos;

    auto up = glm::normalize(mUp);
    auto right = glm::normalize(mRight);
    glm::vec3 direction(0.0f);
    direction += right * offsetPos.x;
    direction += up * offsetPos.y;

    mPosition = glm::vec3{0.0f, 0.0f, 1.0f} + direction;

    mX = wayPoint.getX() - mSize.width  / 2.0;
    mY = wayPoint.getY() - mSize.height / 2.0;
}


void TransformState::setBearingXY(const ScreenCoordinate &anchor, double bearing) {
    glm::mat4 rotationMatrix{1.0f};
    rotationMatrix = glm::rotate(rotationMatrix, (float) bearing, glm::vec3(0.0f, 0.0f, 1.0f));

    // 更新Up/mRight向量
    mUp = rotationMatrix * glm::vec4(mUp, 0.0f);
    mRight = rotationMatrix * glm::vec4(mRight, 0.0f);

    // 根据锚点，更新Pos位置
    double x = (anchor.x * 2 - mSize.width) / mSize.width;
    double y = ((mSize.height - anchor.y) * 2 - mSize.height) / mSize.height;

    glm::vec3 anchorVec3 = glm::vec3(x, y, 0.0f);
    glm::vec4 offsetPos = glm::vec4(mPosition - anchorVec3, 1.0f);

    offsetPos = rotationMatrix * offsetPos;
    mPosition = glm::vec3(offsetPos) + anchorVec3;
}

void TransformState::setBearingXY(double bearing)
{
    glm::mat4 rotationMatrix{1.0f};
    rotationMatrix = glm::rotate(rotationMatrix, (float) bearing, glm::vec3(0.0f, 0.0f, 1.0f));

    glm::vec4 up = glm::vec4(0.0f, 1.0f, 0.0f, 0.0f);
    glm::vec4 right = glm::vec4(1.0f, 0.0f, 0.0f, 0.0f);

    // 更新Up/mRight向量
    mUp = rotationMatrix * up;
    mRight = rotationMatrix * right;
}


void TransformState::setPitch(double pitch) {
    // 不影响position
    auto mat = glm::rotate(glm::mat4(1.0f), (float) pitch, mRight);
    mUp = mat * glm::vec4(mUp, 0.0f);
}


CameraOptions TransformState::getCameraOptions(const EdgeInsets &padding) const {
    return CameraOptions()
            .withCenter(getWayPoint())
            .withPadding(padding)
            .withZoom(getZoom())
            .withBearing(-mBearing * util::RAD2DEG)
            .withPitch(mPitch * util::RAD2DEG);
}


WayPoint TransformState::getWayPoint() const {
    return {mX + mSize.width  / 2.0, mY + mSize.height  / 2.0};
}

double TransformState::getZoom() const {
    return 0.0;
}

WayPoint TransformState::screenCoordinateToWayPoint(const ScreenCoordinate& point) const
{
    WayPoint wayPoint{ mX + point.x,  mY + point.y};
    return wayPoint;
}

}



