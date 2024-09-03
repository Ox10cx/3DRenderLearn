//
// Created by gongxi on 2024/8/30.
//

#ifndef ASSIMPDEMO_GEO_H
#define ASSIMPDEMO_GEO_H

#include "geometry/point.h"
#include "geometry/point_arithmetic.h"
#include <cmath>
#include <stdexcept>

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


#endif //ASSIMPDEMO_GEO_H
