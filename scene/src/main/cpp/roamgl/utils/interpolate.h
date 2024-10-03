//
// Created by gongxi on 2024/10/3.
//

#ifndef ASSIMPDEMO_INTERPOLATE_H
#define ASSIMPDEMO_INTERPOLATE_H

namespace roamgl {
namespace util {

template<class T, class Enabled = void>
struct Interpolator;

template<typename T>
T interpolate(const T& a, const T& b, const double t) {
    return Interpolator<T>()(a, b, t);
}

template<class T, class Enabled>
struct Interpolator {
     T operator()(const T& a, const T& b, const double t) const {
         return a * (1.0 - t) + b * t;
     }
};



}
}

#endif //ASSIMPDEMO_INTERPOLATE_H
