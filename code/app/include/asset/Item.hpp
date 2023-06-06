#pragma once
#ifndef __NR_ITEM_HPP__
#define __NR_ITEM_HPP__

#include <string>

namespace NRenderer
{
    using namespace std;
    //声明类型别名，GIId是无符号整型
    using GlId = unsigned int;
    struct Item
    {
        string name;
        Item()
            : name      ("undefined")
        {}
    };
    //存储渲染数据
    struct GlDrawData
    {
        vector<Vec3> positions;
    };
    //封装成智能指针
    SHARE(GlDrawData);
}

#endif