//
// Created by 龚喜 on 1/27/24.
//

#ifndef ASSIMPDEMO_SHADER_S_H
#define ASSIMPDEMO_SHADER_S_H

#include "GLFunctions.h"
#include "RenderLogger.h"
#include <string>

GLuint LoadShaders(std::string vertexShaderCode, std::string fragmentShaderCode);
GLuint GetAttributeLocation(GLuint programID, const std::string& variableName);
GLint GetUniformLocation(GLuint programID, const std::string& uniformName);


#endif //ASSIMPDEMO_SHADER_S_H
