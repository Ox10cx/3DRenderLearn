//
// Created by 龚喜 on 1/27/24.
//

#ifndef ASSIMPDEMO_GLCAMERA_H
#define ASSIMPDEMO_GLCAMERA_H

#include <vector>
#include "FileHelper.h"

#define SCALE_TO_Z_TRANSLATION  20
#define TRANSLATION_TO_ANGLE    5
#define XY_TRANSLATION_FACTOR   10


class GLCamera {
public:
    GLCamera(
            float fov = 45,          // in degrees
            float zPosition = 10,    // camera's location on Z axis
            float nearPlaneDistance = 1.0f, // as large as possible
            float farPlaneDistance = 2000.0f // as small as possible
    );
    void        SetModelPosition(std::vector<float> modelPosition);
    void        SetAspectRatio(float aspect);
    glm::mat4   GetMVP(){ return mMvpMat; }
    void        RotateModel(float distanceX, float distanceY, float endPositionX, float endPositionY);
    void        ScaleModel(float scaleFactor);
    void        TranslateModel(float distanceX, float distanceY);


private:
    void        ComputeMVPMatrix();

    float       m_fFOV;
    float       m_fNearPlaneDistance, m_fFarPlaneDistance;

    glm::mat4   mProjectionViewMat;
    glm::mat4   mRotateMat, mTranslateMat;
    glm::mat4   mModelMat;
    glm::mat4   mViewMat;
    glm::mat4   mMvpMat;     // ModelViewProjection: obtained by multiplying Projection, View, & Model

    // six degrees-of-freedom of the model contained in a quaternion and x-y-z coordinates
    glm::quat   mModelQuaternion;
    float       mDeltaX, mDeltaY, mDeltaZ;

};


#endif //ASSIMPDEMO_GLCAMERA_H
