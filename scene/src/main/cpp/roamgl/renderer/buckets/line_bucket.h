//
// Created by gongxi on 2024/10/29.
//

#ifndef ASSIMPDEMO_LINE_BUCKET_H
#define ASSIMPDEMO_LINE_BUCKET_H


#include "programs/segment.h"
#include "programs/line_program.h"
#include "gfx/vertex_vector.h"
#include "gfx/index_vector.h"

#include "gfx/vertex_buffer.h"
#include "gfx/index_buffer.h"
#include "tile/geometry_tile_data.h"

#include <optional>
#include <vector>

namespace roamgl
{

class LineBucket {
public:
    LineBucket(const float zoom,
               const uint32_t overscaling);
    ~LineBucket();

    gfx::VertexVector<LineLayoutVertex> vertices;
    gfx::IndexVector<gfx::Triangles> triangles;
    SegmentVector<LineAttributes> segments;

    std::optional<gfx::VertexBuffer<LineLayoutVertex>> vertexBuffer;
    std::optional<gfx::IndexBuffer> indexBuffer;

    void addGeometry(const GeometryCoordinates&);

private:


    struct TriangleElement {
        TriangleElement(uint16_t a_, uint16_t b_, uint16_t c_) : a(a_), b(b_), c(c_) {}
        uint16_t a, b, c;
    };

    class Distances;
    void addCurrentVertex(const GeometryCoordinate& currentVertex, double& distance,
                          const Point<double>& normal, double endLeft, double endRight, bool round,
                          std::size_t startVertex, std::vector<LineBucket::TriangleElement>& triangleStore,
                          std::optional<Distances> distances);

    void addPieSliceVertex(const GeometryCoordinate& currentVertex, double distance,
                           const Point<double>& extrude, bool lineTurnsLeft, std::size_t startVertex,
                           std::vector<TriangleElement>& triangleStore,
                           std::optional<Distances> distances);

    std::ptrdiff_t e1;
    std::ptrdiff_t e2;
    std::ptrdiff_t e3;

    const float zoom;
    const uint32_t overscaling;

};

}



#endif //ASSIMPDEMO_LINE_BUCKET_H
