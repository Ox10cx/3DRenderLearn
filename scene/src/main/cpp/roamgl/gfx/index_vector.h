//
// Created by gongxi on 2024/10/30.
//

#ifndef ASSIMPDEMO_INDEX_VECTOR_H
#define ASSIMPDEMO_INDEX_VECTOR_H

#include "draw_mode.h"
#include "utils/ignore.h"
#include <vector>


namespace roamgl {
namespace gfx {

template <class DrawMode>
class IndexVector {
public:
    static constexpr std::size_t groupSize = BufferGroupSizeOf<DrawMode>::value;

    template <class... Args>
    void emplace_back(Args&&... args) {
        static_assert(sizeof...(args) == groupSize, "wrong buffer element count");
        util::ignore({ (v.emplace_back(std::forward<Args>(args)), 0)... });
    }

    std::size_t elements() const {
        return v.size();
    }

    std::size_t bytes() const {
        return v.size() * sizeof(uint16_t);
    }

    bool empty() const {
        return v.empty();
    }

    void clear() {
        v.clear();
    }

    const uint16_t* data() const {
        return v.data();
    }

    const std::vector<uint16_t>& vector() const {
        return v;
    }

private:
    std::vector<uint16_t> v;
};

} // namespace gfx
} // namespace roamgl


#endif //ASSIMPDEMO_INDEX_VECTOR_H
