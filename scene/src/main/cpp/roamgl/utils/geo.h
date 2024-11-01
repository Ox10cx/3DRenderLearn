//
// Created by gongxi on 2024/8/30.
//

#ifndef ASSIMPDEMO_GEO_H
#define ASSIMPDEMO_GEO_H

#include <cmath>
#include <stdexcept>
#include "geometry/point.h"
#include "geometry/point_arithmetic.h"

namespace roamgl {

using ScreenCoordinate = geometry::point<double>;

class EdgeInsets {

private:
    double _top;
    double _left;
    double _bottom;
    double _right;

public:
    EdgeInsets(double t_ = 0, double l_ = 0, double b_ = 0, double r_ = 0)
            : _top(t_), _left(l_), _bottom(b_), _right(r_) {
        if (std::isnan(_top)) {
            throw std::domain_error("top must not be NaN");
        }
        if (std::isnan(_left)) {
            throw std::domain_error("left must not be NaN");
        }
        if (std::isnan(_bottom)) {
            throw std::domain_error("bottom must not be NaN");
        }
        if (std::isnan(_right)) {
            throw std::domain_error("right must not be NaN");
        }
    }

    double top() const { return _top; }
    double left() const { return _left; }
    double bottom() const { return _bottom; }
    double right() const { return _right; }

    bool isFlush() const {
        return _top == 0 && _left == 0 && _bottom == 0 && _right == 0;
    }

    void operator+=(const EdgeInsets& o) {
        _top += o._top;
        _left += o._left;
        _bottom += o._bottom;
        _right += o._right;
    }

    EdgeInsets operator+(const EdgeInsets& o) const {
        return {
                _top + o._top, _left + o._left, _bottom + o._bottom, _right + o._right,
        };
    }

    ScreenCoordinate getCenter(uint16_t width, uint16_t height) const;

    friend bool operator==(const EdgeInsets& a, const EdgeInsets& b) {
        return a._top == b._top && a._left == b._left && a._bottom == b._bottom && a._right == b._right;
    }

    friend bool operator!=(const EdgeInsets& a, const EdgeInsets& b) {
        return !(a == b);
    }
};

class WayPoint {
    private:
        double x;
        double y;

    public:

    WayPoint(double x_ = 0, double y_ = 0)
                : x(x_), y(y_) {
            if (std::isnan(x)) {
                throw std::domain_error("WayPoint x must not be NaN");
            }
            if (std::isnan(y)) {
                throw std::domain_error("WayPoint y must not be NaN");
            }
        }

        double getX() const { return x; }
        double getY() const { return y; }

        friend bool operator==(const WayPoint& a, const WayPoint& b) {
            return a.x == b.x && a.y == b.y;
        }

        friend bool operator!=(const WayPoint& a, const WayPoint& b) {
            return !(a == b);
        }
    };


};


#endif //ASSIMPDEMO_GEO_H
