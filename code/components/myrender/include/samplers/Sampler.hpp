#pragma once
#ifndef __SAMPLER_HPP__
#define __SAMPLER_HPP__

#include <mutex>

namespace Photonmap
{
    using std::mutex;
    //���Ի�ȡһ������������ֵ
    class Sampler
    {
    protected:
        static int insideSeed() {
            static mutex m;
            static int seed = 0;
            m.lock();
            seed++;
            m.unlock();
            return seed;
        }
    public:
        virtual ~Sampler() = default;
        Sampler() = default;
    };
}

#endif