//
// Created by gongxi on 2024/8/29.
//

#ifndef ASSIMPDEMO_PERSPECTIVE_CAMERA_H
#define ASSIMPDEMO_PERSPECTIVE_CAMERA_H

#include "camera.h"

class PerspectiveCamera : public Camera {
public:
    PerspectiveCamera(float fov = 45.0f, float aspect = 1.0f, float near = 1.0f, float far = 1.0f);
    ~PerspectiveCamera();

    glm::mat4 getProjectionMatrix() override;

    void scale(float scale) override;

private:
    float mFov {45.0f};
    float mAspect {1.0f};
};


#endif //ASSIMPDEMO_PERSPECTIVE_CAMERA_H
