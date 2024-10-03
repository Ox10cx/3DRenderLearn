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
        auto p2 = p / worldSize(scale);
        return WayPoint {p2.x - 0.5,  0.5 - p2.y};
    }

private:
    static Point<double> project_(const WayPoint& wayPoint, double worldSize) {
        return Point<double> {
                0.5 + wayPoint.getX(),
                0.5 - wayPoint.getY()
        } * worldSize ;

    }


};


}



#endif //ASSIMPDEMO_PROJECTION_H
