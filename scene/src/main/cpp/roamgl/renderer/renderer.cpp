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

        mShader = std::make_unique<Shader>(assetManager_, pathToInternalDir, "shaders/line2.vert",
                                           "shaders/line2.frag");
        mGeometry = std::move(Geometry::createLine());
    }

    Renderer::~Renderer() {

    }

    void Renderer::render(const UpdateParameters &parms) {
        GLCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
        // 2 清理画布
        GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

        glm::mat4 proj = parms.transformState.getProjMatrix();

        glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3 (299.5, 300.0, 0.0));


//    mShader->begin();
//    mShader->setUniformValue("sampler", 0);
//    mShader->setUniformValue("projectMatrix", parms.transformState.getProjMatrix() * model);

//        mShader->begin();
//        mShader->setUniformValue("projectMatrix", parms.transformState.getProjMatrix() * model);
//        mShader->setUniformValue("u_halfheight", 600 / 2.0f);
//        mShader->setUniformValue("u_width", 0.001f);
//        mShader->setUniformValue("u_gapwidth", 0.01f);
//        mShader->setUniformValue("u_color", glm::vec4 {1.0f, 1.0f, 1.0f, 1.0f});

//        uniform mat4 u_matrix;
//        uniform mediump float u_ratio;
//        uniform vec2 u_units_to_pixels;
//        uniform lowp float u_device_pixel_ratio;
//
//
//        uniform mediump float u_gapwidth;
//        uniform lowp float u_offset;
//        uniform mediump float u_width;

//        uniform highp vec4 u_color;
//        uniform lowp float u_blur;
//        uniform lowp float u_opacity;


//        u_ratio   0.0625
//        u_units_to_pixels     =   2.0f  / state.getSize().width, -2.0f / state.getSize().height
//        device_pixel_ratio = 1

//        gapwidth = 0.0
//        offset = 0.0
//        u_width = 1.0
//        ucolor = 1.0f, 1.0f, 1.0f, 1.0f
//        u_blur = 0.0
//        u_opacity = 1.0


        mShader->begin();
        mShader->setUniformValue("u_matrix", parms.transformState.getProjMatrix() * model);
        mShader->setUniformValue("u_ratio", 0.0625f);
        mShader->setUniformValue("u_units_to_pixels", glm::vec2{2.0f  / 800, -2.0f / 600});
        mShader->setUniformValue("u_device_pixel_ratio", 1.0f);

        mShader->setUniformValue("u_gapwidth", 0.0f);
        mShader->setUniformValue("u_offset", 0.0f);
        mShader->setUniformValue("u_width", 0.01f);

        mShader->setUniformValue("u_blur", 0.0f);
        mShader->setUniformValue("u_opacity", 1.0f);
        mShader->setUniformValue("u_color", glm::vec4 {1.0f, 0.0f, 1.0f, 1.0f});


        GLCall(glBindVertexArray(mGeometry->getVao()));

        GLCall(glDrawElements(GL_TRIANGLES, mGeometry->getIndicesCount(), GL_UNSIGNED_SHORT, 0));

        GLCall(glBindVertexArray(0));

        mShader->end();
    }

}
