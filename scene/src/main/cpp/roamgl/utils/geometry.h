//
// Created by gongxi on 2024/9/5.
//

#ifndef ASSIMPDEMO_GEOMETRY_H
#define ASSIMPDEMO_GEOMETRY_H

#include "geometry/point.h"
#include "geometry/point_arithmetic.h"
#include <cstdint>

namespace roamgl {

enum class FeatureType : uint8_t {
    Unknown = 0,
    Point = 1,
    LineString = 2,
    Polygon = 3
};

template <class T>
using Point = geometry::point<T>;


template <class S, class T>
Point<S> convertPoint(const Point<T>& p) {
    return Point<S>(p.x, p.y);
}

}



#endif //ASSIMPDEMO_GEOMETRY_H
