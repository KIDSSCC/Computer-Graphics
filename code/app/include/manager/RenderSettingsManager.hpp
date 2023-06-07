#pragma once
#ifndef __NR_RENDER_SETTINGS_MANAGER_HPP__
#define __NR_RENDER_SETTINGS_MANAGER_HPP__

#include "scene/Camera.hpp"

namespace NRenderer
{
    //管理渲染设置
    struct RenderSettings
    {
        //宽，高，深
        unsigned int width;
        unsigned int height;
        unsigned int depth;

        //采样数
        unsigned int samplesPerPixel;
        RenderSettings()
            : width             (500)
            , height            (500)
            , depth             (4)
            , samplesPerPixel   (16)
        {}
    };

    //环境光设置
    struct AmbientSettings
    {
        //固定颜色或使用纹理
        enum Type
        {
            CONSTANT, ENVIROMENT_MAP
        };
        //环境光的类型，
        Type type = Type::CONSTANT;
        //颜色
        RGB ambient = {0, 0, 0};
        //贴图
        Handle mapTexture = {};
    };
    //相机设置
    struct RenderSettingsManager
    {
        //统一管理相机，渲染设置，环境光设置
        Camera camera = {};
        RenderSettings renderSettings = {};
        AmbientSettings ambientSettings = {};
    };
    
}

#endif