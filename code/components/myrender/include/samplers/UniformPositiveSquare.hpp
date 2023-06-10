#pragma once
#ifndef __UNIFORM_POSITIVE_SQUARE_HPP__
#define __UNIFORM_POSITIVE_SQUARE_HPP__

#include "Sampler2d.hpp"
#include <ctime>

namespace Photonmap
{
    using namespace std;
    //¶þÎ¬²É0-1£¬
    class UniformPositiveSquare : public Sampler2d
    {
    private:
        default_random_engine e;
        uniform_real_distribution<float> u;
    public:
        UniformPositiveSquare()
            : e                 ((unsigned int)time(0) + insideSeed())
            , u                 (0, 1)
        {}
        Vec2 sample2d() override {
            return { u(e),u(e) };
        }
    };
}

#endif