//
// Created by gongxi on 2024/10/10.
//

#ifndef ASSIMPDEMO_WRAP_H
#define ASSIMPDEMO_WRAP_H

#include <cmath>

namespace roamgl
{

namespace util
{

template <typename T>
T wrap(T value, T min, T max) {
    if (value >= min && value < max) {
        return value;
    } else if (value == max) {
        return min;
    }

    const T delta = max - min;
    const T wrapped = min + std::fmod(value - min, delta);
    return value < min ? wrapped + delta : wrapped;
}


}

}

#endif //ASSIMPDEMO_WRAP_H
