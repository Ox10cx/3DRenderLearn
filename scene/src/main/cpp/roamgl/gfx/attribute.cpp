//
// Created by gongxi on 2024/10/30.
//


#include "attribute.h"

#include <limits>
#include <cassert>

namespace roamgl {
namespace gfx {

std::optional<AttributeBinding> offsetAttributeBinding(const std::optional<AttributeBinding>& binding, std::size_t vertexOffset) {
    assert(vertexOffset <= std::numeric_limits<uint32_t>::max());
    if (binding) {
        AttributeBinding result = *binding;
        result.vertexOffset = static_cast<uint32_t>(vertexOffset);
        return result;
    } else {
        return binding;
    }
}

} // namespace gfx
} // namespace mbgl