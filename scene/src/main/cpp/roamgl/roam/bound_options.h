//
// Created by gongxi on 2024/11/17.
//

#ifndef ASSIMPDEMO_BOUND_OPTIONS_H
#define ASSIMPDEMO_BOUND_OPTIONS_H

#include "geo.h"

#include <optional>

namespace roamgl {

struct BoundOptions {
    BoundOptions& withWayPointBounds(WayPointBounds b) {bounds = b; return *this;}

    BoundOptions& withMinZoom(double z) {minZoom = z; return *this;}

    BoundOptions& withMaxZoom(double z) {maxZoom = z; return *this;}

    std::optional<WayPointBounds> bounds;

    std::optional<double> maxZoom;

    std::optional<double> minZoom;
};

}


#endif //ASSIMPDEMO_BOUND_OPTIONS_H
