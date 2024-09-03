//
// Created by 龚喜 on 2024/8/23.
//

#include "gl_geometry.h"

Geometry::Geometry() {

}

Geometry::~Geometry() {
    GLCall(glDeleteVertexArrays(1, &mVao));
    GLCall(glDeleteBuffers(1, &mPosVbo));
    GLCall(glDeleteBuffers(1, &mUvVbo));
    GLCall(glDeleteBuffers(1, &mEbo));
}

std::unique_ptr<Geometry> Geometry::createPlane(float width, float height)
{
    auto geometry = std::make_unique<Geometry>();

    geometry->mIndicesCount = 6;

    float halfW = width / 2.0f;
    float halfH = height / 2.0f;

    float positions[] = {
            -halfW, -halfH, 0.0f,
            halfW, -halfH, 0.0f,
            halfW, halfH, 0.0f,
            -halfW, halfH, 0.0f,
    };

    float uvs[] = {
            0.0f, 0.0f,
            1.0f, 0.0f,
            1.0f, 1.0f,
            0.0f, 1.0f
    };

    unsigned int indices[] = {
            0, 1, 2,
            2, 3, 0
    };

    // 生成VBO
    unsigned int& posVbo = geometry->mPosVbo;
    GLCall(glGenBuffers(1, &posVbo));
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, posVbo));
    GLCall(glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW));

    unsigned int& uvVbo = geometry->mUvVbo;
    GLCall(glGenBuffers(1, &uvVbo));
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, uvVbo));
    GLCall(glBufferData(GL_ARRAY_BUFFER, sizeof (uvs), uvs, GL_STATIC_DRAW));

    unsigned int& ebo = geometry->mEbo;
    GLCall(glGenBuffers(1, &ebo));
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, ebo));
    GLCall(glBufferData(GL_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW));

    // 生成VAO
    unsigned int& vao = geometry->mVao;
    GLCall(glGenVertexArrays(1, &vao));
    GLCall(glBindVertexArray(vao));

    // 绑定VBO
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, posVbo));
    GLCall(glEnableVertexAttribArray(0));
    GLCall(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float ) * 3, (void*) 0));

    GLCall(glBindBuffer(GL_ARRAY_BUFFER, uvVbo));
    GLCall(glEnableVertexAttribArray(1));
    GLCall(glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof (float) * 2, (void*)0));

    //绑定EBO
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo));

    //解绑VAO
    GLCall(glBindVertexArray(0));

    return geometry;
}

//Geometry* Geometry::createPlane(float width, float height)
//{
//    Geometry *geometry = new Geometry();
//    geometry->mIndicesCount = 6;
//
//    float halfW = width / 2.0f;
//    float halfH = height / 2.0f;
//
//    float positions[] = {
//            -halfW, -halfH, 0.0f,
//            halfW, -halfH, 0.0f,
//            halfW, halfH, 0.0f,
//            -halfW, halfH, 0.0f,
//    };
//
//    float uvs[] = {
//            0.0f, 0.0f,
//            1.0f, 0.0f,
//            1.0f, 1.0f,
//            0.0f, 1.0f
//    };
//
//    unsigned int indices[] = {
//            0, 1, 2,
//            2, 3, 0
//    };
//
//    // 生成VBO
//    unsigned int& posVbo = geometry->mPosVbo;
//    GLCall(glGenBuffers(1, &posVbo));
//    GLCall(glBindBuffer(GL_ARRAY_BUFFER, posVbo));
//    GLCall(glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW));
//
//    unsigned int& uvVbo = geometry->mUvVbo;
//    GLCall(glGenBuffers(1, &uvVbo));
//    GLCall(glBindBuffer(GL_ARRAY_BUFFER, uvVbo));
//    GLCall(glBufferData(GL_ARRAY_BUFFER, sizeof (uvs), uvs, GL_STATIC_DRAW));
//
//    unsigned int& ebo = geometry->mEbo;
//    GLCall(glGenBuffers(1, &ebo));
//    GLCall(glBindBuffer(GL_ARRAY_BUFFER, ebo));
//    GLCall(glBufferData(GL_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW));
//
//    // 生成VAO
//    unsigned int& vao = geometry->mVao;
//    GLCall(glGenVertexArrays(1, &vao));
//    GLCall(glBindVertexArray(vao));
//
//    // 绑定VBO
//    GLCall(glBindBuffer(GL_ARRAY_BUFFER, posVbo));
//    GLCall(glEnableVertexAttribArray(0));
//    GLCall(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float ) * 3, (void*) 0));
//
//    GLCall(glBindBuffer(GL_ARRAY_BUFFER, uvVbo));
//    GLCall(glEnableVertexAttribArray(1));
//    GLCall(glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof (float) * 2, (void*)0));
//
//    //绑定EBO
//    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo));
//
//    //解绑VAO
//    GLCall(glBindVertexArray(0));
//}

//Geometry *Geometry::createBox(float size) {
////    Geometry *geomerty = new Geometry();
////
////    float halfSize = size / 2.0f;
////    float positions[] = {
////            -halfSize, -halfSize, -halfSize,   // 左下后
////            halfSize, -halfSize, -halfSize,   // 右下后
////            halfSize,  halfSize, -halfSize,   // 右上后
////            -halfSize,  halfSize, -halfSize,   // 左上后
////            -halfSize, -halfSize,  halfSize,   // 左下前
////            halfSize, -halfSize,  halfSize,   // 右下前
////            halfSize,  halfSize,  halfSize,   // 右上前
////            -halfSize,  halfSize,  halfSize,   // 左上前
////    };
////
////    float uvs[] = {
////            0.0f, 0.0f,
////            1.0f, 0.0f,
////            1.0f, 1.0f,
////            0.0f, 1.0f,
////
////            0.0f, 1.0f,
////            1.0f, 1.0f,
////            0.0f, 0.0f,
////            1.0f, 0.0f,
////    };
////
////    // 立方体索引数据
////    unsigned int indices[] = {
////            // 后面
////            0, 1, 2,
////            2, 3, 0,
////            // 前面
////            4, 5, 6,
////            6, 7, 4,
////            // 左面
////            0, 4, 7,
////            7, 3, 0,
////            // 右面
////            1, 5, 6,
////            6, 2, 1,
////            // 底面
////            0, 1, 5,
////            5, 4, 0,
////            // 顶面
////            3, 2, 6,
////            6, 7, 3
////    };
////
////    geomerty->mIndicesCount = sizeof (indices) / sizeof (unsigned int);
//
//
//
//}