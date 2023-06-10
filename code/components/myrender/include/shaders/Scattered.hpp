#pragma once
#ifndef __SCATTERED_HPP__
#define __SCATTERED_HPP__

#include "Ray.hpp"

namespace Photonmap
{
    struct Scattered
    {
        //ɢ���Ĺ���
        Ray ray = {};
        //˥��ϵ��
        Vec3 attenuation = {};
        //ɢ��Ĺ�����ɫ
        Vec3 emitted = {};
        //ɢ�䷽��ĸ����ܶȺ���
        float pdf = {0.f};
    };
    
}

#endif