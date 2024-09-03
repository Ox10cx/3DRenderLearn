//
// Created by gongxi on 2024/9/2.
//

#ifndef ASSIMPDEMO_TRANSFORM_H
#define ASSIMPDEMO_TRANSFORM_H

#include "geo.h"
#include "camera.h"
#include "transform_state.h"


class Transform {


public:
    Transform();
    ~Transform();

    void resize(const Size size);

    void moveBy(const ScreenCoordinate& offset);

    void earseTo(const CameraOptions&);

    const TransformState& getState() const {return mState; }

private:
    TransformState mState;

};


#endif //ASSIMPDEMO_TRANSFORM_H
