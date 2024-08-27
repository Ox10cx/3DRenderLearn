//
// Created by 龚喜 on 1/27/24.
//

#include "GLFunctions.h"
#include "RenderLogger.h"
#include "gl_functions.h"
#include <sstream>


/**
 * Basic initializations for GL.
 */
void GLInit() {
    GLCall(glClear(1));

    // White background
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

    GLCall(glClear(-1));

    // Enable depth test
    glEnable(GL_DEPTH_TEST);
    // Accept fragment if it closer to the camera than the former one
    glDepthFunc(GL_LEQUAL);

    LOGI("OpenGL %s, GLSL %s", glGetString(GL_VERSION), glGetString(GL_SHADING_LANGUAGE_VERSION));

    // check if the device supports GLES 3 or GLES 2
    const char* versionStr = (const char*)glGetString(GL_VERSION);
    if (strstr(versionStr, "OpenGL ES 3.")) {
        LOGD("Device supports GLES 3");
    } else {
        LOGD("Device supports GLES 2");
    }

    CheckGLError("MyGLInits");
}

/**
 * Checks for OpenGL errors.
 */
void CheckGLError(const std::string& funcName){

    GLenum err = glGetError();
    if (err == GL_NO_ERROR) {
        return;
    } else {
        LOGF("[FAIL GL] %s", funcName.c_str());
    }

    switch(err) {

        case GL_INVALID_ENUM:
            LOGE("GL_INVALID_ENUM: GLenum argument out of range");
            break;

        case GL_INVALID_VALUE:
            LOGE("GL_INVALID_VALUE: numeric argument out of range");
            break;

        case GL_INVALID_OPERATION:
            LOGE("GL_INVALID_OPERATION: operation illegal in current state");
            break;

        case GL_INVALID_FRAMEBUFFER_OPERATION:
            LOGE("GL_INVALID_FRAMEBUFFER_OPERATION: framebuffer object is not complete");
            break;

        case GL_OUT_OF_MEMORY:
            LOGE( "GL_OUT_OF_MEMORY: not enough memory left to execute command");
            break;

        default:
            LOGE("unlisted error");
            break;
    }
}