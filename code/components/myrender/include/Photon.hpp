#pragma once
#ifndef __PHOTON_HPP__
#define __PHOTON_HPP__
namespace Photonmap
{
    // 定义光子结构体
    struct Photon {
        Vec3 position;
        Vec3 direction;
        Vec3 power;
        

        Photon(Vec3 v1, Vec3 v2, Vec3 v3)
            :position(v1)
            , direction(v2)
            , power(v3) {}
    };
}

#endif