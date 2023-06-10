#pragma once
#ifndef __PHOTON_HPP__
#define __PHOTON_HPP__
namespace Photonmap
{
    // 定义光子结构体
    struct Photon {
        Vec3 position;
        Vec3 power;
        Vec3 direction;
    };
}

#endif