#pragma once
#ifndef __SAMPLER_3D_HPP__
#define __SAMPLER_3D_HPP__

#include "Sampler.hpp"

#include <random>
#include "geometry/vec.hpp"

namespace Photonmap
{
    using NRenderer::Vec3;
    //三维采样得到一个Vec3
    class Sampler3d : public Sampler
    {
        
    public:
        Sampler3d() = default;
        virtual Vec3 sample3d() = 0;
    };
}

#endif