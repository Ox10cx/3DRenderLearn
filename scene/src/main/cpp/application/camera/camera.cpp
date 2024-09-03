//
// Created by gongxi on 2024/8/29.
//

#include "camera.h"

Camera::Camera()
{

}

Camera::~Camera()
{

}

glm::mat4 Camera::getViewMatrix()
{
    glm::vec3 front = glm::cross(mUp, mRight);
    glm::vec3 center = front + mPosition;
    return glm::lookAt(mPosition, center, mUp);
}
glm::mat4 Camera::getProjectionMatrix()
{
    return glm::identity<glm::mat4>();
}

void Camera::scale(float scale) {

}
