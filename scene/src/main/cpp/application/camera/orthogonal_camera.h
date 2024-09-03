//
// Created by gongxi on 2024/8/29.
//

#ifndef ASSIMPDEMO_ORTHOGONAL_CAMERA_H
#define ASSIMPDEMO_ORTHOGONAL_CAMERA_H
#include "camera.h"

class OrthogonalCamera : public Camera {
public:
    OrthogonalCamera(float left = -1.0, float right = 1.0f, float bottom = -1.0f, float top = 1.0f, float near = 1.0f, float far = -1.0f);
    ~OrthogonalCamera();

    glm::mat4 getProjectionMatrix() override;

    void scale(float scale) override;

private:
    float mLeft    {-1.0f};
    float mRight   {1.0f};
    float mBottom  {-1.0f};
    float mTop     {1.0f};
    float mNear    {1.0f};
    float mFar    {-1.0f};
    float mScale  {0.0f};

};


#endif //ASSIMPDEMO_ORTHOGONAL_CAMERA_H
