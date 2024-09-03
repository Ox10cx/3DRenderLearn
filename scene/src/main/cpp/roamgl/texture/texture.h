//
// Created by 龚喜 on 2024/8/27.
//

#ifndef ASSIMPDEMO_TEXTURE_H
#define ASSIMPDEMO_TEXTURE_H

#include <string>
#include <android/asset_manager.h>

class Texture {
public:
    Texture();
    Texture(AAssetManager *assetManager, const std::string &pathToInternalDir, const std::string& path, unsigned int unit);
    ~Texture();

    void bind();
    void unBind();

private:
    unsigned int mTexture{0};
    int mWidth  {0};
    int mHeight {0};
    unsigned int mUnit {0};
};


#endif //ASSIMPDEMO_TEXTURE_H
