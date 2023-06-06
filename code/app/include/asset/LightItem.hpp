#pragma once
#ifndef __NR_LIGHT_ITEM_HPP__
#define __NR_LIGHT_ITEM_HPP__

#include "scene/Light.hpp"
#include "Item.hpp"

namespace NRenderer
{
    using namespace std;
    // 继承自Item，Item中只有一个name成员
    struct LightItem : public Item
    {
        //opengl顶点数组对象
        GlId glVAO{0};
        GlId glVBO{0};
        GlId glEBO{0};
        //智能指针，光源对象
        SharedLight light;
        //Item中的渲染数据对象，这里是他的智能指针。
        SharedGlDrawData externalDrawData;
    };
    
    
} // namespace NRenderer


#endif