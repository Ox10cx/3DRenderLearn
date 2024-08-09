//
// Created by 龚喜 on 1/27/24.
//

#ifndef ASSIMPDEMO_GLFUNCTIONS_H
#define ASSIMPDEMO_GLFUNCTIONS_H

#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#include <stdio.h>
#include <string>

void GLInit();
void CheckGLError(const std::string& funcName);

#endif //ASSIMPDEMO_GLFUNCTIONS_H
