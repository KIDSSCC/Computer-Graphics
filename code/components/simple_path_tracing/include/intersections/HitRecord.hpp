#pragma once
#ifndef __HIT_RECORD_HPP__
#define __HIT_RECORD_HPP__

#include <optional>

#include "geometry/vec.hpp"

//光线的追踪记录？
namespace SimplePathTracer
{
    using namespace NRenderer;
    using namespace std;
    //定义了光线和物体相交的结构
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