//
// Created by 龚喜 on 2024/8/23.
//

#ifndef ASSIMPDEMO_GL_GEOMETRY_H
#define ASSIMPDEMO_GL_GEOMETRY_H
#include "gl_core.h"

class Geometry {
public:
    Geometry();
    ~Geometry();

//    static Geometry* createBox(float size);
//   static Geometry* createPlane(float width, float height);

   static std::unique_ptr<Geometry> createPlane(float width, float height);


    unsigned int getVao() const {return mVao;}
    uint32_t getIndicesCount() const { return mIndicesCount;}

private:
    unsigned int mVao {0};
    unsigned int mPosVbo {0};
    unsigned int mUvVbo {0};
    unsigned int mEbo {0};
    uint32_t mIndicesCount {0};
};


#endif //ASSIMPDEMO_GL_GEOMETRY_H
