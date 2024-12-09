//
// Created by gongxi on 2024/10/28.
//

#ifndef ASSIMPDEMO_GEOMETRY_TILE_DATA_H
#define ASSIMPDEMO_GEOMETRY_TILE_DATA_H

#include "utils/geometry.h"
#include <vector>

namespace roamgl {

using GeometryCoordinate =  Point<int16_t>;

class GeometryCoordinates : public std::vector<GeometryCoordinate> {
public:
    using coordinate_type = float;

    GeometryCoordinates(std::initializer_list<GeometryCoordinate> args)
            : std::vector<GeometryCoordinate>(std::move(args)) {}

    template <class... Args>
    GeometryCoordinates(Args&&... args) : std::vector<GeometryCoordinate>(std::forward<Args>(args)...) {}
};



}



#endif //ASSIMPDEMO_GEOMETRY_TILE_DATA_H
