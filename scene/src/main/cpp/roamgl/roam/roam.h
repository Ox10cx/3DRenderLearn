//
// Created by gongxi on 2024/8/30.
//

#ifndef ASSIMPDEMO_ROAM_H
#define ASSIMPDEMO_ROAM_H
#include <memory>
#include "utils/geo.h"
#include "roam/roam_options.h"


class RendererFrontend;

class Roam {
public:
    explicit Roam(RendererFrontend&, const RoamOptions&);
    ~Roam();

    void setSize(const Size);

    void moveBy(const ScreenCoordinate&);

protected:
    class Impl;
    const std::unique_ptr<Impl> mImpl;

};


#endif //ASSIMPDEMO_ROAM_H
