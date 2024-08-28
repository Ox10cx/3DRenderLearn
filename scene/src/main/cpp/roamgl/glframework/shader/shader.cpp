//
// Created by 龚喜 on 2024/8/26.
//

#include "shader.h"
#include "log.h"
#include "file_utils.h"
#include <fstream>
#include <sstream>


Shader::Shader(AAssetManager *assetManager, const std::string &pathToInternalDir,
               const std::string &vertexPath, const std::string &fragmentPath)
               {
    unsigned int vs = compileShader(GL_VERTEX_SHADER, parseShader(assetManager, pathToInternalDir, vertexPath));
    unsigned int fs = compileShader(GL_FRAGMENT_SHADER, parseShader(assetManager, pathToInternalDir, fragmentPath));

    GLCall(mProgram = glCreateProgram());
    GLCall(glAttachShader(mProgram, vs));
    GLCall(glAttachShader(mProgram, fs));
    GLCall(glLinkProgram(mProgram));
    GLCall(glValidateProgram(mProgram));

    int result;
    GLCall(glGetProgramiv(mProgram, GL_LINK_STATUS, &result));
    if (result == GL_FALSE)
    {
        int length;
        GLCall(glGetProgramiv(mProgram, GL_INFO_LOG_LENGTH, &length));
        char *message = (char *)alloca(length * sizeof(char *));
        GLCall(glGetProgramInfoLog(mProgram, length, &length, message));

        Log::Info(Event::Shader, "Failed to Link %s", message);
    }
    GLCall(glDeleteShader(vs));
    GLCall(glDeleteShader(fs));
}

Shader::~Shader() {
    Log::Info(Event::Shader, "Delete Shader %s");
    GLCall(glDeleteProgram(mProgram));
}

std::string Shader::parseShader(AAssetManager* assetManager, const std::string &pathToInternalDir, const std::string& assetFilepath)
{
    std::string fullPath = pathToInternalDir + "/" + FileUtils::GetFileName(assetFilepath);
    bool isFilePresent = FileUtils::ExtractAssetReturnFilename(assetManager, fullPath, assetFilepath);
    if(!isFilePresent) {
        return "";
    }

    std::ifstream stream(fullPath);
    std::string line;
    std::stringstream ss;
    while (getline(stream, line)) {
        ss << line << '\n';
    }
    Log::Info(Event::Shader, "Shader File Content %s", ss.str().c_str());

    return ss.str();
}

unsigned int Shader::compileShader(unsigned int type, const std::string& source)
{
    if (source.empty()) return 0;

    // 1、创建shader程序
    unsigned int id = GLCall(glCreateShader(type));

    // 2、为shader程序输入shader代码
    const char* src = source.c_str();
    GLCall(glShaderSource(id, 1, &src, nullptr));

    // 3、编译shader代码
    GLCall(glCompileShader(id));

    // 4、查看编译结果
    int result;
    GLCall(glGetShaderiv(id, GL_COMPILE_STATUS, &result));
    if (result == GL_FALSE)
    {
        int length;
        GLCall(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length));
        char *message = (char *)alloca(length * sizeof(char *));
        GLCall(glGetShaderInfoLog(id, length, &length, message));

        std::string shaderType = type == GL_VERTEX_SHADER ? " vertexShader" : "fragmentShader";
        Log::Error(Event::Shader, "Failed to compile %s shader !", shaderType.c_str());
        Log::Error(Event::Shader, " %s ", message);
        GLCall(glDeleteShader(id));
        return 0;
    }
    return id;
}

void Shader::begin()
{
    GLCall(glUseProgram(mProgram));
}
void Shader::end()
{
    GLCall(glUseProgram(0));
}

// vs 与 fs 的shader 的Uniform 重名的时候，都会起作用
void Shader::setUniformValue(const std::string& name, float value)
{
    // 通过名称拿到Uniform的位置
    GLuint locaiton = GLCall(glGetUniformLocation(mProgram, name.c_str()));

    // 通过location来更新Uniform变量
    GLCall(glUniform1f(locaiton, value));
}

void Shader::setUniformValue(const std::string& name, float* value)
{
    // 通过名称拿到Uniform的位置
    GLuint locaiton = GLCall(glGetUniformLocation(mProgram, name.c_str()));

    // 通过location来更新Uniform变量
    GLCall(glUniform3fv(locaiton,  1, value));
}

void Shader::setUniformValue(const std::string& name, const glm::vec3& value)
{
    // 通过名称拿到Uniform的位置
    GLuint locaiton = GLCall(glGetUniformLocation(mProgram, name.c_str()));

    // 通过location来更新Uniform变量
    GLCall(glUniform3f(locaiton,  value.x, value.y, value.z));
}

void Shader::setUniformValue(const std::string& name, int value) {
    // 通过名称拿到Uniform的位置
    GLuint locaiton = GLCall(glGetUniformLocation(mProgram, name.c_str()));

    // 通过location来更新Uniform变量
    GLCall(glUniform1i(locaiton, value));
}

void Shader::setUniformValue(const std::string& name, const glm::mat4& value) {
    // 通过名称拿到Uniform的位置
    GLuint locaiton = GLCall(glGetUniformLocation(mProgram, name.c_str()));
    // opengl 和 glm 矩阵的存储方式都是列存储，所以不需要转置
    GLCall(glUniformMatrix4fv(locaiton, 1, GL_FALSE, glm::value_ptr(value)));
}

void Shader::setUniformValue(const std::string& name, const glm::mat3& value) {
    // 通过名称拿到Uniform的位置
    GLuint locaiton = GLCall(glGetUniformLocation(mProgram, name.c_str()));
    // opengl 和 glm 矩阵的存储方式都是列存储，所以不需要转置
    GLCall(glUniformMatrix3fv(locaiton, 1, GL_FALSE, glm::value_ptr(value)));
}

void Shader::setUniformValue(const std::string& name, const glm::mat4* value, int count) {
    // 通过名称拿到Uniform的位置
    GLuint locaiton = GLCall(glGetUniformLocation(mProgram, name.c_str()));
    // opengl 和 glm 矩阵的存储方式都是列存储，所以不需要转置
    GLCall(glUniformMatrix4fv(locaiton, count, GL_FALSE, glm::value_ptr(value[0])));
}