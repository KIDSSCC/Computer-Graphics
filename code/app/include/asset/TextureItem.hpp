#pragma once
#ifndef __NR_TEXTURE_ITEM_HPP__
#define __NR_TEXTURE_ITEM_HPP__

#include "scene/Texture.hpp"
#include "Item.hpp"
#include "utilities/GlImage.hpp"
namespace NRenderer
{
    //继承自Item，
    struct TextureItem : public Item
    {
        //纹理对象的智能指针
        SharedTexture texture;
        //openGL纹理对象的ID
        GlImageId glId;
    };
} // namespace NRenderer


#endif