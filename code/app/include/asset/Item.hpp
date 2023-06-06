#pragma once
#ifndef __NR_ITEM_HPP__
#define __NR_ITEM_HPP__

#include <string>

namespace NRenderer
{
    using namespace std;
    //�������ͱ�����GIId���޷�������
    using GlId = unsigned int;
    struct Item
    {
        string name;
        Item()
            : name      ("undefined")
        {}
    };
    //�洢��Ⱦ����
    struct GlDrawData
    {
        vector<Vec3> positions;
    };
    //��װ������ָ��
    SHARE(GlDrawData);
}

#endif