//
// Created by gongxi on 2024/10/30.
//

#ifndef ASSIMPDEMO_ATTRIBUTES_H
#define ASSIMPDEMO_ATTRIBUTES_H

#include "gfx/attribute.h"

namespace roamgl {
namespace attributes {

// Layout attributes

ROAMGL_DEFINE_ATTRIBUTE(int16_t, 2, pos);
ROAMGL_DEFINE_ATTRIBUTE(int16_t, 2, extrude);
ROAMGL_DEFINE_ATTRIBUTE(int16_t, 4, pos_offset);
ROAMGL_DEFINE_ATTRIBUTE(int16_t, 2, pos_normal);
ROAMGL_DEFINE_ATTRIBUTE(float, 3, projected_pos);
ROAMGL_DEFINE_ATTRIBUTE(int16_t, 2, label_pos);
ROAMGL_DEFINE_ATTRIBUTE(int16_t, 2, anchor_pos);
ROAMGL_DEFINE_ATTRIBUTE(uint16_t, 2, texture_pos);
ROAMGL_DEFINE_ATTRIBUTE(int16_t,  4, normal_ed);
ROAMGL_DEFINE_ATTRIBUTE(float, 1, fade_opacity);
ROAMGL_DEFINE_ATTRIBUTE(uint8_t, 2, placed);
ROAMGL_DEFINE_ATTRIBUTE(uint16_t, 3, size);
ROAMGL_DEFINE_ATTRIBUTE(float, 1, offset);
ROAMGL_DEFINE_ATTRIBUTE(float, 2, shift);

template <typename T, std::size_t N>
struct data {
    using Type = gfx::AttributeType<T, N>;
    static constexpr auto name() {
        return "data";
    }
};

// Paint attributes

ROAMGL_DEFINE_ATTRIBUTE(float, 2, color);
ROAMGL_DEFINE_ATTRIBUTE(float, 2, fill_color);
ROAMGL_DEFINE_ATTRIBUTE(float, 2, halo_color);
ROAMGL_DEFINE_ATTRIBUTE(float, 2, stroke_color);
ROAMGL_DEFINE_ATTRIBUTE(float, 2, outline_color);
ROAMGL_DEFINE_ATTRIBUTE(float, 1, opacity);
ROAMGL_DEFINE_ATTRIBUTE(float, 1, stroke_opacity);
ROAMGL_DEFINE_ATTRIBUTE(float, 1, blur);
ROAMGL_DEFINE_ATTRIBUTE(float, 1, radius);
ROAMGL_DEFINE_ATTRIBUTE(float, 1, width);
ROAMGL_DEFINE_ATTRIBUTE(float, 1, floorwidth);
ROAMGL_DEFINE_ATTRIBUTE(float, 1, height);
ROAMGL_DEFINE_ATTRIBUTE(float, 1, base);
ROAMGL_DEFINE_ATTRIBUTE(float, 1, gapwidth);
ROAMGL_DEFINE_ATTRIBUTE(float, 1, stroke_width);
ROAMGL_DEFINE_ATTRIBUTE(float, 1, halo_width);
ROAMGL_DEFINE_ATTRIBUTE(float, 1, halo_blur);
ROAMGL_DEFINE_ATTRIBUTE(float, 1, weight);
ROAMGL_DEFINE_ATTRIBUTE(uint16_t, 4, pattern_to);
ROAMGL_DEFINE_ATTRIBUTE(uint16_t, 4, pattern_from);

} // namespace attributes

using PositionOnlyLayoutAttributes = TypeList<attributes::pos>;

} // namespace roamgl


#endif //ASSIMPDEMO_ATTRIBUTES_H
