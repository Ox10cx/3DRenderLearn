//
// Created by 龚喜 on 2024/8/26.
//

#ifndef ASSIMPDEMO_RENDERER_H
#define ASSIMPDEMO_RENDERER_H

#include <android/asset_manager.h>
#include <string>
#include "shader.h"
#include "gl_geometry.h"

class Renderer {
public:
    Renderer(AAssetManager *assetManager_, const std::string& pathToInternalDir);
    ~Renderer();

    void render();

private:
    std::unique_ptr<Shader> mShader;
    std::unique_ptr<Geometry> mGeometry;

};


#endif //ASSIMPDEMO_RENDERER_H
