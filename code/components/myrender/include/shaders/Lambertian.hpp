#pragma once
#ifndef __LAMBERTIAN_HPP__
#define __LAMBERTIAN_HPP__

#include "Shader.hpp"

namespace Photonmap
{
    class Lambertian : public Shader
    {
    private:
        //�洢��������ʵ���ɫ
        Vec3 albedo;
    public:
        Lambertian(Material& material, vector<Texture>& textures);
        Scattered shade(const Ray& ray, const Vec3& hitPoint, const Vec3& normal) const;
    };
}

#endif