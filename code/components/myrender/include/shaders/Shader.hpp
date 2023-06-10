#pragma once
#ifndef __SHADER_HPP__
#define __SHADER_HPP__

#include "geometry/vec.hpp"
#include "common/macros.hpp"
#include "scene/Scene.hpp"

#include "Ray.hpp"
#include "shaders/Scattered.hpp"

namespace Photonmap
{
    using namespace NRenderer;
    using namespace std;

    constexpr float PI = 3.1415926535898f;
    //渲染时的着色器
    class Shader
    {
    protected:
        //材质与纹理的引用
        Material& material;
        vector<Texture>& textureBuffer;
    public:
        Shader(Material& material, vector<Texture>& textures)
            : material              (material)
            , textureBuffer         (textures)
        {}
        virtual Scattered shade(const Ray& ray, const Vec3& hitPoint, const Vec3& normal) const = 0;
    };
    SHARE(Shader);
}

#endif