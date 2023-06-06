#pragma once
#ifndef __NR_MODEL_ITEM_HPP__
#define __NR_MODEL_ITEM_HPP__

#include "scene/Model.hpp"
#include "Item.hpp"

#include "glad/glad.h"

namespace NRenderer
{
    using namespace std;
    //继承自Item，
    struct ModelItem : public Item
    {
        //模型对象的智能指针
        SharedModel model{nullptr};
    };

    struct NodeItem : public Item
    {
        //opengl顶点数组，初始化为0
        GlId glVAO{0};
        GlId glVBO{0};
        GlId glEBO{0};
        //节点对象智能指针
        SharedNode node{nullptr};
        //渲染对象智能指针
        SharedGlDrawData externalDrawData{nullptr};
    };
    
    
} // namespace NRenderer


#endif