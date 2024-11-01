//
// Created by gongxi on 2024/9/3.
//

#ifndef ASSIMPDEMO_CONSTANTS_H
#define ASSIMPDEMO_CONSTANTS_H
#include <cmath>

namespace roamgl
{

namespace util
{


    constexpr int32_t EXTENT = 8192;

    constexpr double DEG2RAD = M_PI / 180.0;
    constexpr double RAD2DEG = 180.0 / M_PI;

    constexpr double tileSize = 512;
    constexpr double M2PI = M_PI * 2;

    constexpr double PITCH_MIN = 0.0;
    constexpr double PITCH_MAX = M_PI / 3;

    constexpr double MIN_ZOOM = 0.0;
    constexpr double MAX_ZOOM = 25.5;
    constexpr float  MIN_ZOOM_F = MIN_ZOOM;
    constexpr float  MAX_ZOOM_F = MAX_ZOOM;
    constexpr uint8_t DEFAULT_MAX_ZOOM = 22;
}

}

#endif //ASSIMPDEMO_CONSTANTS_H
