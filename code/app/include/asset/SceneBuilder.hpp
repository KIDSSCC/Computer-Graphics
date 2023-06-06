#pragma once
#ifndef __NR_SCENE_BUILDER_HPP__
#define __NR_SCENE_BUILDER_HPP__

#include "Asset.hpp"
#include "scene/Scene.hpp"
#include "manager/RenderSettingsManager.hpp"

namespace NRenderer
{
    //构建场景
    class SceneBuilder
    {
    private:
    protected:
        //场景资源
        const Asset& asset;
        //渲染设置
        const RenderSettings& renderSettings;
        //相机对象
        const Camera& camera;
        //环境光照设置
        const AmbientSettings& ambientSettings;
        //场景对象的智能指针
        SharedScene scene;

        //构造渲染选项
        void buildRenderOption();
        //构造缓冲区
        void buildBuffer();
        //构造相机对象
        void buildCamera();
        //构造环境光照
        void buildAmbient();
        //场景是否创建成功的标志位
        bool success;
    public:
        SceneBuilder(const Asset& asset, const RenderSettings& renderSettings, const AmbientSettings& ambientSettings, const Camera& camera)
            : asset             (asset)
            , renderSettings    (renderSettings)
            , ambientSettings   (ambientSettings)
            , camera            (camera)
            , scene             (nullptr)
            , success           (true)
        {}
        SharedScene build();
    };
}

#endif