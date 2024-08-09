//
// Created by 龚喜 on 1/27/24.
//

#ifndef ASSIMPDEMO_FILEHELPER_H
#define ASSIMPDEMO_FILEHELPER_H

#include <stdio.h>
#include <string>
#include "RenderLogger.h"
#include "GLM.h"

std::string GetFileName(const std::string& fileName);

std::string GetDirectoryName(const std::string& fullFileName);

void PrintGLMMat4(const glm::mat4& testMat);

#endif //ASSIMPDEMO_FILEHELPER_H
