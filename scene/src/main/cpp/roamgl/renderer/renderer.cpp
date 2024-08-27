//
// Created by 龚喜 on 2024/8/26.
//

#include "renderer.h"
#include "gl_core.h"
#include "log.h"


Renderer::Renderer(AAssetManager *assetManager_, const std::string& pathToInternalDir)
{
    const char* glVersion;
    GLCall(glVersion = (const char*)glGetString(GL_VERSION));

    const char* glslVersion;
    GLCall(glslVersion = (const char*)glGetString(GL_SHADING_LANGUAGE_VERSION));
    Log::Info(Event::OpenGL, "OpenGL %s, GLSL %s", glVersion, glslVersion);

    mShader = std::make_unique<Shader>(assetManager_, pathToInternalDir, "shaders/white.vert", "shaders/white.frag");
    mGeometry = std::move(Geometry::createPlane(0.5f, 0.5f));
}

Renderer::~Renderer()
{

}

void Renderer::render()
{
    GLCall(glClearColor(1.0f, 1.0f, 1.0f, 1.0f));
    // 2 清理画布
    GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

    mShader->begin();

    GLCall(glBindVertexArray(mGeometry->getVao()));


    // GLCall(glDrawArrays(GL_TRIANGLES, 0, 3));
    Log::Info(Event::OpenGL, "OpenGL getIndicesCount %d", mGeometry->getIndicesCount());
    GLCall(glDrawElements(GL_TRIANGLES, mGeometry->getIndicesCount(), GL_UNSIGNED_INT, 0));

    GLCall(glBindVertexArray(0));

    mShader->end();
}
