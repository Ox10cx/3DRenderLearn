//
// Created by gongxi on 2024/9/2.
//

#ifndef ASSIMPDEMO_TRANSFORM_STATE_H
#define ASSIMPDEMO_TRANSFORM_STATE_H

#include "glm/glm_core.h"
#include "utils/size.h"
#include "utils/geo.h"


class TransformState {
    friend class Transform;

public:
    TransformState();

    ~TransformState();

    Size getSize() const;

    glm::mat4 getProjMatrix() const;


public:
    void setScreenCoordinate(const ScreenCoordinate &screenCoordinate, double zoom);

private:
    double mX{0.0};
    double mY{0.0};
    double mBearing{0.0};
    double mScale{1.0};
    double mFov{45.0f};
    double mPitch{0.0f};

    Size mSize;

    EdgeInsets mEdgeInsets;

    glm::vec3 mPosition{0.0f, 0.0f, 1.0f};
    glm::vec3 mUp{0.0f, 1.0f, 0.0f};
    glm::vec3 mRight{1.0f, 0.0f, 0.0f};
};


#endif //ASSIMPDEMO_TRANSFORM_STATE_H
