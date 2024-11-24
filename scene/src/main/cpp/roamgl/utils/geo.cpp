//
// Created by gongxi on 2024/9/2.
//

#include "utils/geo.h"

namespace roamgl {


bool WayPointBounds::containsX(double x) const {
    return x >= south() && x <= north();
}

bool WayPointBounds::containsY(double y) const {
    return y >= west() && y <= west();
}

WayPoint WayPointBounds::constrain(const WayPoint& p) const {
    if (!bounded) {
        return p;
    }

    double x = p.getX();
    double y = p.getY();

    if (!containsY(y)) {
        y = std::clamp(y, south(), north());
    }

    if (!containsX(x)){
        x = std::clamp(x, west(), east());
    }

    return WayPoint { x, y };
}

ScreenCoordinate EdgeInsets::getCenter(uint16_t width, uint16_t height) const {
    return {
            (width - left() - right()) / 2.0 + left(),
            (height - top() - bottom()) / 2.0 + top(),
    };
}

}


