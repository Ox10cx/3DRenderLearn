//
// Created by gongxi on 2024/8/29.
//

#ifndef ASSIMPDEMO_CAMERA_H
#define ASSIMPDEMO_CAMERA_H

#include <glm/glm_core.h>

class Camera {
public:
    Camera();
    ~Camera();

    glm::mat4 getViewMatrix();

    virtual glm::mat4 getProjectionMatrix();

    virtual void scale(float scale);

public:
    glm::vec3 mPosition{0.0f, 0.0f, 2.0f};
    glm::vec3 mUp {0.0f, 1.0f, 0.0f};
    glm::vec3 mRight {1.0f, 0.0f, 0.0f};

    float mNear {0.0f};
    float mFar {0.0};

};


#endif //ASSIMPDEMO_CAMERA_H
