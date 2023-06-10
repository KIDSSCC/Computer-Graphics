#pragma once
#ifndef __SCATTERED_HPP__
#define __SCATTERED_HPP__

#include "Ray.hpp"

namespace Photonmap
{
    struct Scattered
    {
        //散射后的光线
        Ray ray = {};
        //衰减系数
        Vec3 attenuation = {};
        //散射的光照颜色
        Vec3 emitted = {};
        //散射方向的概率密度函数
        float pdf = {0.f};
    };
    
}

#endif