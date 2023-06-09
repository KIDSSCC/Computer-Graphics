#pragma once
#ifndef __SAMPLER_1D_HPP__
#define __SAMPLER_1D_HPP__

#include "Sampler.hpp"

#include <random>

namespace Photonmap
{
    //继承自Sampler，一维采样得到一个浮点数
    class Sampler1d : protected Sampler
    {
    public:
        Sampler1d() = default;
        virtual float sample1d() = 0;
    };
}

#endif