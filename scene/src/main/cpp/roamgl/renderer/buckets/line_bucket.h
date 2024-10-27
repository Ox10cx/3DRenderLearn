//
// Created by gongxi on 2024/10/26.
//

#ifndef ASSIMPDEMO_LINE_BUCKET_H
#define ASSIMPDEMO_LINE_BUCKET_H

#include <vector>
#include "glm/glm_core.h"

namespace roamgl {

#define LineCapTypeButt    1   //  无端点
#define LineCapTypeRound    2    //  圆端点
#define LineCapTypeSquare    3    // 方端点

#define LineJoinTypeMiter        1    // 尖角
#define LineJoinTypeBevel        2    //缺角
#define LineJoinTypeFlipBevel    3
#define LineJoinTypeRound        4    // 圆角
#define LineJoinTypeFakeRound    5

#define DOUBLE_INFINITY     (9999999999.0)
#define UINT16_INFINITY     (65536)


    struct LineLayoutVertex {
        std::vector<glm::vec3> mPos;
        std::vector<glm::vec4> mData;
        std::vector<glm::vec3> mNormal;
        std::vector<glm::vec2> mDir;

        int size();

        void
        add(glm::vec3 p, glm::vec3 e, bool roundX, bool roundY, int8_t dir, int32_t linesofar = 0);

        std::vector<glm::vec3> &getPos();

        std::vector<glm::vec4> &getData();

        std::vector<glm::vec3> &getNormal();

        std::vector<glm::vec2> &getDir();

        void reset();
    };

    struct TriangleElement {
        TriangleElement(uint32_t a_, uint32_t b_, uint32_t c_) : a(a_), b(b_), c(c_) {}

        uint32_t a, b, c;
    };


    class LineBucket {
    public:
        LineBucket();

        ~LineBucket();

        void addGeometry(const std::vector<glm::vec3> &coordinates, double dHalfHeight);

        void addCurrentVertex(glm::vec3 currentCoordinate,
                              double &distance,
                              glm::vec3 normal,
                              double endLeft,
                              double endRight,
                              bool round,
                              int startVertex,
                              std::vector<TriangleElement> &triangleStore);

        void addPieSliceVertex(glm::vec3 currentVertex,
                               double distance,
                               glm::vec3 extrude,
                               bool lineTurnsLeft,
                               std::size_t startVertex,
                               std::vector<TriangleElement> &triangleStore);

        std::vector<glm::vec3> &getPos();

        std::vector<glm::vec4> &getData();

        std::vector<glm::vec3> &getNormal();

        std::vector<glm::vec2> &getDir();

        std::vector<int> &getIndexBuffer();

    private:
        int e1;
        int e2;
        int e3;
        uint32_t overscaling;
        double SHARP_CORNER_OFFSET;
        double extrudeScale;
        LineLayoutVertex vertices;
        std::vector<int> mTriangles;
    };

}


#endif //ASSIMPDEMO_LINE_BUCKET_H
