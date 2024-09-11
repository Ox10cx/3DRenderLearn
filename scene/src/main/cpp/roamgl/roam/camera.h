//
// Created by gongxi on 2024/9/2.
//

#ifndef ASSIMPDEMO_CAMERA_H
#define ASSIMPDEMO_CAMERA_H

#include "utils/geo.h"
#include <optional>

namespace roamgl {

struct CameraOptions {
    CameraOptions& withCenter(const std::optional<WayPoint>& o) { center = o; return *this; }
    CameraOptions& withPadding(const std::optional<EdgeInsets>& p) { padding = p; return *this; }
    CameraOptions& withAnchor(const std::optional<ScreenCoordinate>& o) { anchor = o; return *this; }
    CameraOptions& withZoom(const std::optional<double>& o) { zoom = o; return *this; }
    CameraOptions& withBearing(const std::optional<double>& o) { bearing = o; return *this; }
    CameraOptions& withPitch(const std::optional<double>& o) { pitch = o; return *this; }

    std::optional<WayPoint> center;

    std::optional<EdgeInsets> padding;

    std::optional<ScreenCoordinate> anchor;

    std::optional<double> zoom;

    std::optional<double> bearing;

    std::optional<double> pitch;
};

constexpr bool operator==(const CameraOptions& a, const CameraOptions& b) {
    return a.center == b.center
           && a.padding == b.padding
           && a.anchor == b.anchor
           && a.zoom == b.zoom
           && a.bearing == b.bearing
           && a.pitch == b.pitch;
}

constexpr bool operator!=(const CameraOptions& a, const CameraOptions& b) {
    return !(a == b);
}

}

#endif //ASSIMPDEMO_CAMERA_H
