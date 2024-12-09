//
// Created by gongxi on 2024/10/30.
//

#ifndef ASSIMPDEMO_DRAW_SCOPE_H
#define ASSIMPDEMO_DRAW_SCOPE_H

#include <memory>
#include <cassert>

namespace roamgl {
namespace gfx {

class DrawScopeResource {
protected:
    DrawScopeResource() = default;
public:
    virtual ~DrawScopeResource() = default;
};

class DrawScope {
public:
    explicit DrawScope(std::unique_ptr<DrawScopeResource> resource_) : resource(std::move(resource_)) {
    }

    template <typename T = DrawScopeResource>
    T& getResource() const {
        assert(resource);
        return static_cast<T&>(*resource);
    }

protected:
    std::unique_ptr<DrawScopeResource> resource;
};

} // namespace gfx
} // namespace roamgl



#endif //ASSIMPDEMO_DRAW_SCOPE_H
