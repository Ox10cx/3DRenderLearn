//
// Created by gongxi on 2024/9/2.
//

#ifndef ASSIMPDEMO_CAMERA_H
#define ASSIMPDEMO_CAMERA_H

#include <optional>
#include "utils/geo.h"
#include "utils/chrono.h"
#include "utils/unitbezier.hpp"


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

/** Various options for describing a transition between viewpoints with
    animation. All fields are optional; the default values depend on how this
    struct is used. */
struct AnimationOptions {
    /** Time to animate to the viewpoint defined herein. */
    std::optional<Duration> duration;

    /** Average velocity of a flyTo() transition, measured in screenfuls per
        second, assuming a linear timing curve.

        A <i>screenful</i> is the visible span in pixels. It does not correspond
        to a fixed physical distance but rather varies by zoom level. */
    std::optional<double> velocity;

    /** Zero-based zoom level at the peak of the flyTo() transition’s flight
        path. */
    std::optional<double> minZoom;

    /** The easing timing curve of the transition. */
    std::optional<roamgl::util::UnitBezier> easing;

    /** A function that is called on each frame of the transition, just before a
        screen update, except on the last frame. The first parameter indicates
        the elapsed time as a percentage of the duration. */
    std::function<void(double)> transitionFrameFn;

    /** A function that is called once on the last frame of the transition, just
        before the corresponding screen update. */
    std::function<void()> transitionFinishFn;

    /** Creates an animation with no options specified. */
    AnimationOptions() {}

    /** Creates an animation with the specified duration. */
    AnimationOptions(Duration d)
            : duration(d) {}
};

}

#endif //ASSIMPDEMO_CAMERA_H
