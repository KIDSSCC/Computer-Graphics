#pragma once
#ifndef __NR_MODEL_ITEM_HPP__
#define __NR_MODEL_ITEM_HPP__

#include "scene/Model.hpp"
#include "Item.hpp"

#include "glad/glad.h"

namespace NRenderer
{
    using namespace std;
    //�̳���Item��
    struct ModelItem : public Item
    {
        //ģ�Ͷ��������ָ��
        SharedModel model{nullptr};
    };

    struct NodeItem : public Item
    {
        //opengl�������飬��ʼ��Ϊ0
        GlId glVAO{0};
        GlId glVBO{0};
        GlId glEBO{0};
        //�ڵ��������ָ��
        SharedNode node{nullptr};
        //��Ⱦ��������ָ��
        SharedGlDrawData externalDrawData{nullptr};
    };
    
    
} // namespace NRenderer


#endif