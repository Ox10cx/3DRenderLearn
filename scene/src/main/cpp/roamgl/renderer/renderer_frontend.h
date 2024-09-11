//
// Created by gongxi on 2024/8/30.
//

#ifndef ASSIMPDEMO_RENDERER_FRONTEND_H
#define ASSIMPDEMO_RENDERER_FRONTEND_H

#include <memory>

namespace roamgl
{

class UpdateParameters;

class RendererFrontend {
public:
    virtual ~RendererFrontend() = default;

    virtual void update(std::shared_ptr<UpdateParameters>) = 0;
};

}


#endif //ASSIMPDEMO_RENDERER_FRONTEND_H
