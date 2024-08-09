//
// Created by 龚喜 on 1/27/24.
//

#ifndef ASSIMPDEMO_ASSIMPMODEL_H
#define ASSIMPDEMO_ASSIMPMODEL_H

#include "RenderLogger.h"
#include "GLFunctions.h"
#include "GLCamera.h"
#include "AssimpLoader.h"
#include <sstream>
#include <iostream>
#include <stdio.h>
#include <string>


class AssimpModel {
public:
    AssimpModel();
    ~AssimpModel();
    void    PerformGLInits();
    void    Render();
    void    SetViewport(int width, int height);
    void    DoubleTapAction();
    void    ScrollAction(float distanceX, float distanceY, float positionX, float positionY);
    void    ScaleAction(float scaleFactor);
    void    MoveAction(float distanceX, float distanceY);
    int     GetScreenWidth() const { return m_nScreenWidth; }
    int     GetScreenHeight() const { return m_nScreenHeight; }

private:
    int     m_nScreenWidth, m_nScreenHeight;
    std::vector<float> mModelDefaultPosition;
    GLCamera * m_pGLCamera;
    AssimpLoader * m_pAssimpLoader;

};


#endif //ASSIMPDEMO_ASSIMPMODEL_H
