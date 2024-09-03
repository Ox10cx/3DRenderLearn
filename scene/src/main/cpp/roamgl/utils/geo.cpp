//
// Created by gongxi on 2024/9/2.
//

#include "utils/geo.h"


ScreenCoordinate EdgeInsets::getCenter(uint16_t width, uint16_t height) const {
    return {
            (width - left() - right()) / 2.0 + left(),
            (height - top() - bottom()) / 2.0 + top(),
    };
}
