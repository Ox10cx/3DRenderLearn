//
// Created by gongxi on 2024/9/2.
//

#ifndef ASSIMPDEMO_CAMERA_H
#define ASSIMPDEMO_CAMERA_H

#include "utils/geo.h"
#include <optional>


struct CameraOptions {
    CameraOptions& withCenter(const std::optional<ScreenCoordinate>& o) {
        center = o;
        return *this;
    }

    CameraOptions& withAnchor(const std::optional<ScreenCoordinate>& o) {
        anchor = o;
        return *this;
    }

    CameraOptions& withZoom(const std::optional<double>& o) {
        zoom = o;
        return *this;
    }

    CameraOptions& withBearing(const std::optional<double>& o) {
        bearing = o;
        return *this;
    }

    CameraOptions& withPitch(const std::optional<double>& o) {
        pitch = o;
        return *this;
    }


    std::optional<ScreenCoordinate> center;

    std::optional<ScreenCoordinate> anchor;

    std::optional<double> zoom;

    std::optional<double> bearing;

    std::optional<double> pitch;
};

#endif //ASSIMPDEMO_CAMERA_H
