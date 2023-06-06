#pragma once
#ifndef __NR_MATERIAL_ITEM_HPP__
#define __NR_MATERIAL_ITEM_HPP__

#include "scene/Material.hpp"
#include "Item.hpp"

namespace NRenderer
{
    //继承自Item，其中只用一个name
    struct MaterialItem : public Item
    {
        //材料类型的智能指针
        SharedMaterial material;
    };
} // namespace NRenderer


#endif