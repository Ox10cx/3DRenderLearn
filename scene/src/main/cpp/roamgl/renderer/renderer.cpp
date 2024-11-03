//
// Created by 龚喜 on 2024/8/26.
//

#include "renderer.h"
#include "gl_core.h"
#include "log.h"
#include "renderer/update_parameters.h"

namespace roamgl {

    Renderer::Renderer(AAssetManager *assetManager_, const std::string &pathToInternalDir) {
        const char *glVersion = GLCall((const char *) glGetString(GL_VERSION));
        const char *glslVersion = GLCall((const char *) glGetString(GL_SHADING_LANGUAGE_VERSION));
        Log::Info(Event::OpenGL, "OpenGL %s, GLSL %s", glVersion, glslVersion);

//    mShader = std::make_unique<Shader>(assetManager_, pathToInternalDir, "shaders/texture.vert",
//                                       "shaders/texture.frag");
//    mGeometry = std::move(Geometry::createPlane(0.0, 0.0, 1.0f, 1.0f));
//    mTexture = std::make_unique<Texture>(assetManager_, pathToInternalDir, "textures/goku.jpg",
//                                         0);

//        mShader = std::make_unique<Shader>(assetManager_, pathToInternalDir, "shaders/line_origin.vert",
//                                           "shaders/line_origin.frag");

//        mShader = std::make_unique<Shader>(assetManager_, pathToInternalDir, "shaders/line_osg.vert",
//                                           "shaders/line_osg.frag");
//        mGeometry = std::move(Geometry::createLine4());

        mShader = std::make_unique<Shader>(assetManager_, pathToInternalDir, "shaders/line4.vert",
                                           "shaders/line4.frag");
        mGeometry = std::move(Geometry::createLine2());

//        mShader = std::make_unique<Shader>(assetManager_, pathToInternalDir, "shaders/white.vert",
//                                           "shaders/white.frag");
//        mGeometry = std::move(Geometry::createPlane(0.0, 0.0, 1.0f, 1.0f));
    }

    Renderer::~Renderer() {

    }

    void Renderer::render(const UpdateParameters &parms) {
        GLCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
        // 2 清理画布
        GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

        glm::mat4 proj = parms.transformState.getProjMatrix();

        glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3 (glm::vec3 (299.5, 300.0, 0.0)));
//        glm::mat4 model = glm::scale(glm::mat4(1.0f), glm::vec3 (1 / 1000.0, 1 / 1000.0, 0.0));
//        model = glm::translate(model, glm::vec3 (299.5, 300.0, 0.0));


//    mShader->begin();
////    mShader->setUniformValue("sampler", 0);
//    mShader->setUniformValue("projectMatrix",  model);


        mShader->begin();
        mShader->setUniformValue("u_matrix",  proj * model);
        mShader->setUniformValue("u_ratio", 0.625f);
        mShader->setUniformValue("u_units_to_pixels", glm::vec2{1.0f / 0.0027777778450399637, 1.0f / -0.0014064697315916419});
        mShader->setUniformValue("u_device_pixel_ratio", 2.0f);

        mShader->setUniformValue("u_half_height", 400.0f);
        mShader->setUniformValue("u_gapwidth", 0.0f);
        mShader->setUniformValue("u_offset", 0.0f);
        mShader->setUniformValue("u_width", 0.05f);

        mShader->setUniformValue("u_blur", 0.0f);
        mShader->setUniformValue("u_opacity", 1.0f);
        mShader->setUniformValue("u_color", glm::vec4 {1.0f, 0.0f, 1.0f, 1.0f});


        GLCall(glBindVertexArray(mGeometry->getVao()));

        GLCall(glDrawElements(GL_TRIANGLES, mGeometry->getIndicesCount(), GL_UNSIGNED_SHORT, 0));

        GLCall(glBindVertexArray(0));

        mShader->end();
    }

}
