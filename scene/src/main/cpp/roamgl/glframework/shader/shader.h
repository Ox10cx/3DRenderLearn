//
// Created by 龚喜 on 2024/8/26.
//

#ifndef ASSIMPDEMO_SHADER_H
#define ASSIMPDEMO_SHADER_H

#include <android/asset_manager.h>
#include <string>
#include "gl_core.h"

class Shader {
public:
    Shader(AAssetManager* assetManager, const std::string &pathToInternalDir, const std::string& vertexPath, const std::string& fragmentPath);
    ~Shader();
    void begin();
    void end();
    void setUniformValue(const std::string& name, float value);
    void setUniformValue(const std::string& name, float* value);
    void setUniformValue(const std::string& name, const glm::vec3& value);
    void setUniformValue(const std::string& name, int value);
    void setUniformValue(const std::string& name, const glm::mat4& value);
    void setUniformValue(const std::string& name, const glm::mat4* value, int count);
    void setUniformValue(const std::string& name, const glm::mat3& value);

private:
    unsigned int compileShader(unsigned int type, const std::string& source);
    std::string parseShader(AAssetManager* assetManager, const std::string &pathToInternalDir, const std::string& assetFilepath);

private:
    unsigned int mProgram {0};
};


#endif //ASSIMPDEMO_SHADER_H
