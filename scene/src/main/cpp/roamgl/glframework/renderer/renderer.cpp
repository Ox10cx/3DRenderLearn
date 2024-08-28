//
// Created by 龚喜 on 2024/8/26.
//

#include "renderer.h"
#include "gl_core.h"
#include "log.h"


Renderer::Renderer(AAssetManager *assetManager_, const std::string& pathToInternalDir)
{
    const char* glVersion = GLCall((const char*)glGetString(GL_VERSION));
    const char* glslVersion = GLCall((const char*)glGetString(GL_SHADING_LANGUAGE_VERSION));
    Log::Info(Event::OpenGL, "OpenGL %s, GLSL %s", glVersion, glslVersion);

    mShader = std::make_unique<Shader>(assetManager_, pathToInternalDir, "shaders/texture.vert", "shaders/texture.frag");
    mGeometry = std::move(Geometry::createPlane(1.0f, 1.0f));
    mTexture = std::make_unique<Texture>(assetManager_, pathToInternalDir, "textures/wall.jpg", 0);
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
    mShader->setUniformValue("sampler", 0);

    GLCall(glBindVertexArray(mGeometry->getVao()));

    GLCall(glDrawElements(GL_TRIANGLES, mGeometry->getIndicesCount(), GL_UNSIGNED_INT, 0));

    GLCall(glBindVertexArray(0));

    mShader->end();
}
