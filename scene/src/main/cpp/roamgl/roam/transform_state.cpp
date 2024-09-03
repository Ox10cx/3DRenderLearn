//
// Created by gongxi on 2024/9/2.
//

#include "transform_state.h"


TransformState::TransformState()
{

}

TransformState::~TransformState()
{

}

glm::mat4 TransformState::getProjMatrix() const
{
    glm::vec3 front = glm::cross(mUp, mRight);
    glm::vec3 center = front + mPosition;
    return glm::lookAt(mPosition, center, mUp);
}



Size TransformState::getSize() const
{
    return mSize;
}

void TransformState::setScreenCoordinate(const ScreenCoordinate &screenCoordinate, double zoom)
{
    mX = screenCoordinate.x;
    mY = screenCoordinate.y;

    float offsetX = mX * 2 - mSize.width;
    float offsetY = mY * 2 - mSize.height;
    float dx =  offsetX / mSize.width;
    float dy =  -offsetY / mSize.height;

    auto up = glm::normalize(mUp);
    auto right = glm::normalize(mRight);
    glm::vec3 direction(0.0f);
    direction += right * dx;
    direction += up * dy;
    mPosition += direction;
}

