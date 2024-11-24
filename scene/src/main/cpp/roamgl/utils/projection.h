//
// Created by gongxi on 2024/10/3.
//

#ifndef ASSIMPDEMO_PROJECTION_H
#define ASSIMPDEMO_PROJECTION_H

#include "utils/constants.h"
#include "utils/geometry.h"
#include "utils/geo.h"

namespace roamgl {

class Projection {
public:
    static double worldSize(double scale) {
        return scale * util::tileSize;
    }

    static Point<double> project(const WayPoint& wayPoint, double scale) {
        return project_(wayPoint, worldSize(scale));
    }

    static WayPoint unproject(const Point<double>& p, double scale) {
        auto p2 = p * util::WAY_POINT_DISTANCE_MAX / worldSize(scale);
        return WayPoint {p2.x - util::WAY_POINT_X_MAX,  util::WAY_POINT_Y_MAX - p2.y};
    }

private:
    static Point<double> project_(const WayPoint& wayPoint, double worldSize) {
        return Point<double> {
                util::WAY_POINT_X_MAX + wayPoint.getX(),
                util::WAY_POINT_Y_MAX - wayPoint.getY()
        } * (worldSize / util::WAY_POINT_DISTANCE_MAX) ;

    }
};

}



#endif //ASSIMPDEMO_PROJECTION_H
