//
// Created by 龚喜 on 2024/8/26.
//

#include <vector>
#include "renderer.h"
#include "gl_core.h"
#include "log.h"
#include "renderer/update_parameters.h"

namespace roamgl {

Renderer::Renderer(AAssetManager *assetManager_, const std::string &pathToInternalDir) {
    const char *glVersion = GLCall((const char *) glGetString(GL_VERSION));
    const char *glslVersion = GLCall((const char *) glGetString(GL_SHADING_LANGUAGE_VERSION));
    Log::Info(Event::OpenGL, "OpenGL %s, GLSL %s", glVersion, glslVersion);

    mShader = std::make_unique<Shader>(assetManager_, pathToInternalDir, "shaders/texture.vert",
                                       "shaders/texture.frag");

    mGeometry = std::move(Geometry::createPlane(0.0, 0.0, 400.0f, 300.0f));
    mTexture = std::make_unique<Texture>(assetManager_, pathToInternalDir, "textures/goku.jpg",
                                         0);

//    Point<double> p1 = Projection::project({ -0.5, -0.5},  1.0);
//    Point<double> p2 = Projection::project({  0.5, -0.5},  1.0);
//    Point<double> p3 = Projection::project({  0.5,  0.5},  1.0);
//    Point<double> p4 = Projection::project({ -0.5,  0.5},  1.0);

//    std::vector<float> pos = {
//            (float)p1.x, (float)p1.y, 0.0f,
//            (float)p2.x, (float)p2.y, 0.0f,
//            (float)p3.x, (float)p3.y, 0.0f,
//            (float)p4.x, (float)p4.y, 0.0f,
//    };

//    mGeometry = std::move(Geometry::createPlane(pos));
}

Renderer::~Renderer() {

}

void Renderer::render(const UpdateParameters &parms) {
    GLCall(glClearColor(1.0f, 1.0f, 0.0f, 1.0f));
    // 2 清理画布
    GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

    glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3 (300.0, 300.0, 0.0));

    glm::mat4 proj{1.0f};
    parms.transformState.getProjMatrix(proj);

    mShader->begin();
    mShader->setUniformValue("sampler", 0);
    mShader->setUniformValue("projectMatrix", proj * model);

    GLCall(glBindVertexArray(mGeometry->getVao()));

    GLCall(glDrawElements(GL_TRIANGLES, mGeometry->getIndicesCount(), GL_UNSIGNED_INT, 0));

    GLCall(glBindVertexArray(0));

    mShader->end();
}

}
