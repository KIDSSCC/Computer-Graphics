#pragma once
#ifndef __HIT_RECORD_HPP__
#define __HIT_RECORD_HPP__

#include <optional>

#include "geometry/vec.hpp"

//���ߵ�׷�ټ�¼��
namespace Photonmap
{
    using namespace NRenderer;
    using namespace std;
    //�����˹��ߺ������ཻ�Ľṹ
    struct HitRecordBase
    {
        float t;
        Vec3 hitPoint;
        Vec3 normal;
        Handle material;
    };
    using HitRecord = optional<HitRecordBase>;
    inline
    HitRecord getMissRecord() {
        return nullopt;
    }

    inline
    HitRecord getHitRecord(float t, const Vec3& hitPoint, const Vec3& normal, Handle material) {
        return make_optional<HitRecordBase>(t, hitPoint, normal, material);
    }
}

#endif