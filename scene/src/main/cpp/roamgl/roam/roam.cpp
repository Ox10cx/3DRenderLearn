//
// Created by gongxi on 2024/8/30.
//
#include "renderer/renderer_frontend.h"
#include "roam_impl.h"
#include "roam.h"
#include "utils/log.h"

namespace roamgl
{

Roam::Roam(RendererFrontend &frontend,
           const RoamOptions& options)
        : mImpl(std::make_unique<Impl>(frontend, options)) {

}

Roam::~Roam() = default;

void Roam::setSize(const Size size) {
    mImpl->mTransForm.resize(size);
    mImpl->onUpdate();
}

void Roam::moveBy(const roamgl::ScreenCoordinate& point)
{
    mImpl->mTransForm.moveBy(point);
    mImpl->onUpdate();
}

void Roam::easeTo(const roamgl::CameraOptions& camera, const AnimationOptions& animation)
{
    mImpl->mTransForm.easeTo(camera, animation);
    mImpl->onUpdate();
}

ScreenCoordinate Roam::pixelForWayPoint(const WayPoint& wayPoint) const {
    return mImpl->mTransForm.wayPointToScreenCoordinate(wayPoint);
}

WayPoint Roam::wayPointForPixel(const ScreenCoordinate& pixel) const {
    return mImpl->mTransForm.screenCoordinateToWayPoint(pixel);
}


CameraOptions Roam::getCameraOptions(const EdgeInsets& padding) const
{
    return mImpl->mTransForm.getCameraOptions(padding);
}

void Roam::setBounds(const BoundOptions& options) {
    bool changeCamera = false;
    CameraOptions cameraOptions;

    if (options.bounds) {
        changeCamera = true;
        mImpl->mTransForm.setWayPointBounds(*options.bounds);
    }

    if (options.minZoom) {
        mImpl->mTransForm.setMinZoom(*options.minZoom);
        if (mImpl->mTransForm.getZoom() < *options.minZoom) {
            changeCamera = true;
            cameraOptions.withZoom(*options.minZoom);
        }
    }

    if (options.maxZoom) {
        mImpl->mTransForm.setMaxZoom(*options.maxZoom);
        if (mImpl->mTransForm.getZoom() > *options.maxZoom) {
            changeCamera = true;
            cameraOptions.withZoom(*options.maxZoom);
        }
    }

    if (changeCamera) {
        jumpTo(cameraOptions);
    }

}

BoundOptions Roam::getBounds() const {
    return BoundOptions()
            .withWayPointBounds(mImpl->mTransForm.getState().getWayPointBounds())
            .withMinZoom(mImpl->mTransForm.getState().getMinZoom())
            .withMaxZoom(mImpl->mTransForm.getState().getMaxZoom());
}

void Roam::jumpTo(const CameraOptions& camera)  {
    mImpl->jumpTo(camera);
}



CameraOptions Roam::cameraForWayPointBounds(const WayPointBounds& bounds, const EdgeInsets& padding, std::optional<double> bearing, std::optional<double> pitch) const {
    return cameraForWayPoints({
        bounds.northwest(),
        bounds.southwest(),
        bounds.southeast(),
        bounds.northeast(),
        }, padding, bearing, pitch);
}

CameraOptions cameraForWayPoints(const std::vector<WayPoint>& wayPoints, const Transform& transform, const EdgeInsets& padding) {
    if (wayPoints.empty()) {
        return CameraOptions();
    }
    Size size = transform.getState().getSize();
    // Calculate the bounds of the possibly rotated shape with respect to the viewport.
    ScreenCoordinate nePixel = {-INFINITY, -INFINITY};
    ScreenCoordinate swPixel = {INFINITY, INFINITY};
    double viewportHeight = size.height;
    for (WayPoint wayPoint : wayPoints) {
        ScreenCoordinate pixel = transform.wayPointToScreenCoordinate(wayPoint);
        swPixel.x = std::min(swPixel.x, pixel.x);
        nePixel.x = std::max(nePixel.x, pixel.x);
        swPixel.y = std::min(swPixel.y, viewportHeight - pixel.y);
        nePixel.y = std::max(nePixel.y, viewportHeight - pixel.y);
    }
    double width = nePixel.x - swPixel.x;
    double height = nePixel.y - swPixel.y;

    // Calculate the zoom level.
    double minScale = INFINITY;
    if (width > 0 || height > 0) {
        double scaleX = double(size.width) / width;
        double scaleY = double(size.height) / height;
        scaleX -= (padding.left() + padding.right()) / width;
        scaleY -= (padding.top() + padding.bottom()) / height;
        minScale = std::min(scaleX, scaleY);
    }

    double zoom = transform.getZoom();
    if (minScale > 0) {
        zoom = std::clamp(zoom + std::log2(minScale), transform.getState().getMinZoom(), transform.getState().getMaxZoom());
    } else {
        Log::Error(Event::General, "Unable to calculate appropriate zoom level for bounds. Vertical or horizontal padding is greater than map's height or width.");
    }

    // Calculate the center point of a virtual bounds that is extended in all directions by padding.
    ScreenCoordinate centerPixel = nePixel + swPixel;
    ScreenCoordinate paddedNEPixel = {
            padding.right() / minScale,
            padding.top() / minScale,
    };
    ScreenCoordinate paddedSWPixel = {
            padding.left() / minScale,
            padding.bottom() / minScale,
    };
    centerPixel = centerPixel + paddedNEPixel - paddedSWPixel;
    centerPixel /= 2.0;

    // CameraOptions origin is at the top-left corner.
    centerPixel.y = viewportHeight - centerPixel.y;

    return CameraOptions().withCenter(transform.screenCoordinateToWayPoint(centerPixel)).withZoom(zoom);
    }

CameraOptions Roam::cameraForWayPoints(const std::vector<WayPoint>& wayPoints, const EdgeInsets& padding, std::optional<double> bearing, std::optional<double> pitch) const {

    if (!bearing && !pitch) {
        return roamgl::cameraForWayPoints(wayPoints, mImpl->mTransForm, padding);
    }

    Transform transform(mImpl->mTransForm.getState());

    if (bearing || pitch) {
        transform.jumpTo(CameraOptions().withBearing(bearing).withPitch(pitch));
    }

    return roamgl::cameraForWayPoints(wayPoints, transform, padding)
            .withBearing(-transform.getBearing() * util::RAD2DEG)
            .withPitch(transform.getPitch() * util::RAD2DEG);
}


}


