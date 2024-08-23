//
// Created by 龚喜 on 1/27/24.
//

#include "AssimpModel.h"
#include <assimp/Importer.hpp>
#include <opencv2/opencv.hpp>
#include "JNIHelper.h"


AssimpModel::AssimpModel() {
    LOGD("ModelAssimp::ModelAssimp");

    // create MyGLCamera object and set default position for the object
    m_pGLCamera = new GLCamera();
    float pos[]={0.,0.,0.,0.2,0.5,0.};
    std::copy(&pos[0], &pos[5], std::back_inserter(mModelDefaultPosition));
    m_pGLCamera->SetModelPosition(mModelDefaultPosition);

    m_pAssimpLoader = NULL;
}

AssimpModel::~AssimpModel() {

    LOGD("ModelAssimp::ModelAssimpssimp");
    if (m_pGLCamera) {
        delete m_pGLCamera;
    }
    if (m_pAssimpLoader) {
        delete m_pAssimpLoader;
    }
}

/**
 * Perform inits and load the triangle's vertices/colors to GLES
 */
void AssimpModel::PerformGLInits() {

    LOGD("ModelAssimp::PerformGLInits");

    GLInit();

//    m_pAssimpLoader = new AssimpLoader();
//
//    // extract the OBJ and companion files from assets
//    std::string objFilename, mtlFilename, texFilename;
//    bool isFilesPresent  =
//            gHelperObject->ExtractAssetReturnFilename("amenemhat/amenemhat.obj", objFilename) &&
//            gHelperObject->ExtractAssetReturnFilename("amenemhat/amenemhat.mtl", mtlFilename) &&
//            gHelperObject->ExtractAssetReturnFilename("amenemhat/amenemhat.jpg", texFilename);
//    if( !isFilesPresent ) {
//        LOGE("Model %s does not exist!", objFilename.c_str());
//        return;
//    }
//
//    m_pAssimpLoader->Load3DModel(objFilename);

    CheckGLError("ModelAssimp::PerformGLInits");
}


/**
 * Render to the display
 */
void AssimpModel::Render() {

    // clear the screen
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

//    glm::mat4 mvpMat = m_pGLCamera->GetMVP();
//    m_pAssimpLoader->Render3DModel(&mvpMat);

    CheckGLError("ModelAssimp::Render");

}

/**
 * set the viewport, function is also called when user changes device orientation
 */
void AssimpModel::SetViewport(int width, int height) {

    m_nScreenHeight = height;
    m_nScreenWidth = width;
    glViewport(0, 0, width, height);
    CheckGLError("Cube::SetViewport");

//    m_pGLCamera->SetAspectRatio((float) width / height);
}


/**
 * reset model's position in double-tap
 */
void AssimpModel::DoubleTapAction() {

    m_pGLCamera->SetModelPosition(mModelDefaultPosition);
}

/**
 * rotate the model if user scrolls with one finger
 */
void AssimpModel::ScrollAction(float distanceX, float distanceY, float positionX, float positionY) {

    m_pGLCamera->RotateModel(distanceX, distanceY, positionX, positionY);
}

/**
 * pinch-zoom: move the model closer or farther away
 */
void AssimpModel::ScaleAction(float scaleFactor) {

    m_pGLCamera->ScaleModel(scaleFactor);
}

/**
 * two-finger drag: displace the model by changing its x-y coordinates
 */
void AssimpModel::MoveAction(float distanceX, float distanceY) {

    m_pGLCamera->TranslateModel(distanceX, distanceY);
}
