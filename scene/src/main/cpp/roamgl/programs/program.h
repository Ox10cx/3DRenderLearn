//
// Created by gongxi on 2024/10/30.
//

#ifndef ASSIMPDEMO_PROGRAM_H
#define ASSIMPDEMO_PROGRAM_H




#include "gfx/attribute.h"
#include "gfx/draw_mode.h"
#include "programs/segment.h"
#include "programs/attributes.h"


#include <unordered_map>

namespace roamgl
{

template <class Name,
        gfx::PrimitiveType Primitive,
        class LayoutAttributeList>
class Program {
public:
    using LayoutVertex = gfx::Vertex<LayoutAttributeList>;
    using AttributeList = TypeListConcat<LayoutAttributeList>;
};


}

#endif //ASSIMPDEMO_PROGRAM_H
