//
// Created by gongxi on 2024/8/29.
//

#include "orthogonal_camera.h"

OrthogonalCamera::OrthogonalCamera(float left, float right, float bottom, float top, float near, float far)
{
    mLeft = left;
    mRight = right;
    mBottom = bottom;
    mTop = top;
    mNear = near;
    mFar  = far;

}
OrthogonalCamera::~OrthogonalCamera()
{

}


glm::mat4 OrthogonalCamera::getProjectionMatrix()
{
    float scale = std::pow(2.0, mScale);
    return glm::ortho(mLeft * scale, mRight * scale, mBottom * scale, mTop * scale, mNear, mFar);
}

void OrthogonalCamera::scale(float scale)
{
    mScale += scale;
}
