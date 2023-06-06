#pragma once
#ifndef __NR_LIGHT_ITEM_HPP__
#define __NR_LIGHT_ITEM_HPP__

#include "scene/Light.hpp"
#include "Item.hpp"

namespace NRenderer
{
    using namespace std;
    // �̳���Item��Item��ֻ��һ��name��Ա
    struct LightItem : public Item
    {
        //opengl�����������
        GlId glVAO{0};
        GlId glVBO{0};
        GlId glEBO{0};
        //����ָ�룬��Դ����
        SharedLight light;
        //Item�е���Ⱦ���ݶ�����������������ָ�롣
        SharedGlDrawData externalDrawData;
    };
    
    
} // namespace NRenderer


#endif