//
// Created by 龚喜 on 2024/8/26.
//

#ifndef ASSIMPDEMO_RENDERER_H
#define ASSIMPDEMO_RENDERER_H

#include <android/asset_manager.h>
#include <string>
#include "shader/shader.h"
#include "texture/texture.h"
#include "gl_geometry.h"

class Renderer {
public:
    Renderer(AAssetManager *assetManager_, const std::string& pathToInternalDir);
    ~Renderer();

    void render();

private:
    std::unique_ptr<Shader> mShader;
    std::unique_ptr<Geometry> mGeometry;
    std::unique_ptr<Texture> mTexture;

};


#endif //ASSIMPDEMO_RENDERER_H
