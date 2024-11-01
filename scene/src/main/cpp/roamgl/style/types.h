//
// Created by gongxi on 2024/10/28.
//

#ifndef ASSIMPDEMO_TYPES_H
#define ASSIMPDEMO_TYPES_H

#include <cstdint>

namespace roamgl
{

enum class LineCapType : uint8_t {
    Round,
    Butt,
    Square,
};

enum class LineJoinType : uint8_t {
    Miter,
    Bevel,
    Round,
    // the following two types are for internal use only
    FakeRound,
    FlipBevel
};


}


#endif //ASSIMPDEMO_TYPES_H
