//
// Created by 龚喜 on 2024/8/23.
//

#ifndef ASSIMPDEMO_GL_GEOMETRY_H
#define ASSIMPDEMO_GL_GEOMETRY_H
#include "gl_core.h"
#include "renderer/buckets/line_bucket.h"

namespace roamgl {

class Geometry {
public:
    Geometry();
    ~Geometry();

//    static Geometry* createBox(float size);
//   static Geometry* createPlane(float width, float height);

    static std::unique_ptr<Geometry> createPlane(float centerX, float centerY, float width, float height);
    static std::unique_ptr<Geometry> createLine();


    unsigned int getVao() const {return mVao;}
    uint32_t getIndicesCount() const { return mIndicesCount;}




private:
    unsigned int mVao {0};
    unsigned int mPosVbo {0};
    unsigned int mDataVbo {0};
    unsigned int mNormalVbo {0};
    unsigned int mDirVbo {0};


    unsigned int mUvVbo {0};
    unsigned int mEbo {0};
    uint32_t mIndicesCount {0};

     LineBucket *m_pLineBucket;
};

}


#endif //ASSIMPDEMO_GL_GEOMETRY_H
