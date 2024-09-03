//
// Created by gongxi on 2024/8/29.
//

#include "perspective_camera.h"


PerspectiveCamera::PerspectiveCamera(float fov, float aspect, float near, float far)
{
    mFov = fov;
    mAspect = aspect;
    mNear = near;
    mFar = far;
}

PerspectiveCamera::~PerspectiveCamera()
{

}

glm::mat4 PerspectiveCamera::getProjectionMatrix()
{
    return glm::perspective(glm::radians(mFov), mAspect, mNear, mFar);
}

void PerspectiveCamera::scale(float scale)
{
    auto front = glm::cross(mUp, mRight);
    mPosition += (front * scale);
}