//
// Created by 龚喜 on 2024/8/27.
//

#include "texture.h"
#include "gl_core.h"
#include <opencv2/opencv.hpp>
#include "log.h"
#include "file_utils.h"


Texture::Texture()
{

}
Texture::Texture(AAssetManager *assetManager, const std::string &pathToInternalDir, const std::string& path, unsigned int unit)
{
    mUnit = unit;
    std::string fullPath = pathToInternalDir + "/" + FileUtils::GetFileName(path);
    bool isFilePresent = FileUtils::ExtractAssetReturnFilename(assetManager, fullPath, path);
    if(!isFilePresent) {
        return ;
    }

    cv::Mat textureImg = cv::imread(fullPath, cv::ImreadModes::IMREAD_UNCHANGED);
    if (!textureImg.empty()) {
        // opencv reads textures in BGR format, change to RGB for GL
        cv::cvtColor(textureImg, textureImg, cv::COLOR_BGR2RGBA);

        // opencv reads image from top-left, while GL expects it from bottom-left
        // vertically flip the image
        cv::flip(textureImg, textureImg, 0);

        // 生成纹理并且激活单元绑定
        GLCall(glGenTextures(1, &mTexture));
        GLCall(glActiveTexture(GL_TEXTURE0 + unit));
        GLCall(glBindTexture(GL_TEXTURE_2D, mTexture));

        // 传输纹理数据，开辟显存
        GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, textureImg.cols,
                     textureImg.rows, 0, GL_RGBA, GL_UNSIGNED_BYTE,
                     textureImg.data));

        // 自动生成mipmap
        GLCall(glGenerateMipmap(GL_TEXTURE_2D));

        // 设置纹理过滤方式
        GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
        GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));

        // 设置纹理包裹方式
        GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
        GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT));
    } else {
        Log::Error(Event::File, "OpenCv imread fail %s ", path.c_str());
    }

}

Texture::~Texture()
{
    if (mTexture != 0)
    {
        GLCall(glDeleteTextures(1, &mTexture));
    }
}

void Texture::bind()
{
    GLCall(glActiveTexture(GL_TEXTURE0 + mUnit));
    GLCall(glBindTexture(GL_TEXTURE_2D, mTexture));
}
void Texture::unBind()
{
    GLCall(glBindTexture(GL_TEXTURE_2D, 0));
}