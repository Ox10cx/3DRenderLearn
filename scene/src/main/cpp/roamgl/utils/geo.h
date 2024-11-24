//
// Created by gongxi on 2024/8/30.
//

#ifndef ASSIMPDEMO_GEO_H
#define ASSIMPDEMO_GEO_H

#include "geometry/point.h"
#include "geometry/point_arithmetic.h"
#include "constants.h"

#include <vector>
#include <cmath>
#include <stdexcept>

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

class WayPointBounds {
public:
    WayPointBounds()
            : sw({-util::WAY_POINT_X_MAX, -util::WAY_POINT_Y_MAX}), ne({util::WAY_POINT_X_MAX, util::WAY_POINT_Y_MAX}), bounded(false) {}

    // Return a bounds covering the entire (unwrapped) world.
    static WayPointBounds world() {
        return WayPointBounds({-util::WAY_POINT_X_MAX, -util::WAY_POINT_Y_MAX}, {util::WAY_POINT_X_MAX, util::WAY_POINT_Y_MAX});
    }

    // Return the bounds consisting of the single point.
    static WayPointBounds singleton(const WayPoint& a) {
        return WayPointBounds(a, a);
    }

    // Return the convex hull of two points; the smallest bounds that contains both.
    static WayPointBounds hull(const WayPoint& a, const WayPoint& b) {
        WayPointBounds bounds(a, a);
        bounds.extend(b);
        return bounds;
    }

    // Return a bounds that may serve as the identity element for the extend operation.
    static WayPointBounds empty() {
        WayPointBounds bounds = world();
        std::swap(bounds.sw, bounds.ne);
        return bounds;
    }

    static WayPointBounds unbounded() {
        return {};
    }

    bool valid() const {
        return (sw.getX() <= ne.getX()) && (sw.getY() <= ne.getY());
    }

    double south() const { return sw.getY(); }
    double west()  const { return sw.getX(); }
    double north() const { return ne.getY(); }
    double east()  const { return ne.getX(); }

    WayPoint southwest() const { return sw; }
    WayPoint northeast() const { return ne; }
    WayPoint southeast() const { return WayPoint(south(), east()); }
    WayPoint northwest() const { return WayPoint(north(), west()); }

    WayPoint center() const {
        return WayPoint((sw.getX() + ne.getX()) / 2,
                      (sw.getY() + ne.getY()) / 2);
    }

    WayPoint constrain(const WayPoint& p) const;

    void extend(const WayPoint& point) {
        sw = WayPoint(std::min(point.getX(), sw.getX()),
                    std::min(point.getY(), sw.getY()));
        ne = WayPoint(std::max(point.getX(), ne.getX()),
                    std::max(point.getY(), ne.getY()));
    }

    void extend(const WayPointBounds& bounds) {
        extend(bounds.sw);
        extend(bounds.ne);
    }

    bool isEmpty() const {
        return sw.getX() > ne.getX() ||
               sw.getY() > ne.getY();
    }


private:
    WayPoint sw;
    WayPoint ne;
    bool bounded = true;

    WayPointBounds(WayPoint sw_, WayPoint ne_)
            : sw(std::move(sw_)), ne(std::move(ne_)) {}

    bool containsX(double x) const;
    bool containsY(double y) const;

    friend bool operator==(const WayPointBounds& a, const WayPointBounds& b) {
        return (!a.bounded && !b.bounded) || (a.bounded && b.bounded && a.sw == b.sw && a.ne == b.ne);
    }

    friend bool operator!=(const WayPointBounds& a, const WayPointBounds& b) {
        return !(a == b);
    }
};



};


#endif //ASSIMPDEMO_GEO_H
