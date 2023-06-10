#include "server/Server.hpp"
#include "Photonmap.hpp"
#include "VertexTransformer.hpp"
#include "intersections/intersections.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include<iostream>

namespace Photonmap
{
    RGB PhotonmapRender::gamma(const RGB& rgb) {
        return glm::sqrt(rgb);
    }

    void PhotonmapRender::release(const RenderResult& r) {
        auto [p, w, h] = r;
        delete[] p;
    }

    void PhotonmapRender::renderTask(RGBA* pixels, int width, int height, int off, int step)
    {
        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < width; j++)
            {
                Vec3 color{ 0,0,0 };
                float x = (float(j)) / float(width);
                float y = (float(i)) / float(height);
                auto ray = camera.shoot(x, y);
                color = traceRay(ray);
            }
        }
    }

    auto PhotonmapRender::render() -> RenderResult {
        // shaders
        shaderPrograms.clear();
        ShaderCreator shaderCreator{};
        for (auto& m : scene.materials) {
            shaderPrograms.push_back(shaderCreator.create(m, scene.textures));
        }

        RGBA* pixels = new RGBA[width * height]{};

        // 局部坐标转换成世界坐标
        VertexTransformer vertexTransformer{};
        vertexTransformer.exec(spScene);

        const auto taskNums = 1;
        thread t[taskNums];
        for (int i = 0; i < taskNums; i++) {
            t[i] = thread(&PhotonmapRender::renderTask,
                this, pixels, width, height, i, taskNums);
        }
        for (int i = 0; i < taskNums; i++) {
            t[i].join();
        }

        emitPhotons(5);
        getServer().logger.log("Done...");
        return { pixels, width, height };
    }

    //求解最近碰撞物体
    HitRecord PhotonmapRender::closestHitObject(const Ray& r) {
        //最近的交点，默认为空，距离为无穷大
        HitRecord closestHit = nullopt;
        float closest = FLOAT_INF;

        //遍历所有的球体，获取与最近球体的交点
        for (auto& s : scene.sphereBuffer) {
            auto hitRecord = Intersection::xSphere(r, s, 0.000001, closest);
            if (hitRecord && hitRecord->t < closest) {
                closest = hitRecord->t;
                closestHit = hitRecord;
            }
        }
        //遍历所有的三角面片
        for (auto& t : scene.triangleBuffer) {
            auto hitRecord = Intersection::xTriangle(r, t, 0.000001, closest);
            if (hitRecord && hitRecord->t < closest) {
                closest = hitRecord->t;
                closestHit = hitRecord;
            }
        }
        //遍历所有的平面
        for (auto& p : scene.planeBuffer) {
            auto hitRecord = Intersection::xPlane(r, p, 0.000001, closest);
            if (hitRecord && hitRecord->t < closest) {
                closest = hitRecord->t;
                closestHit = hitRecord;
            }
        }
        //返回最近的交点
        return closestHit;
    }

    //获取与当前光线最近的光源的交点信息
    tuple<float, Vec3> PhotonmapRender::closestHitLight(const Ray& r) {
        Vec3 v = {};
        HitRecord closest = getHitRecord(FLOAT_INF, {}, {}, {});

        //遍历所有的区域光源，更新最近交点
        for (auto& a : scene.areaLightBuffer) {
            auto hitRecord = Intersection::xAreaLight(r, a, 0.000001, closest->t);
            if (hitRecord && closest->t > hitRecord->t) {
                closest = hitRecord;
                v = a.radiance;
            }
        }
        //返回最近的距离和辐射强度
        return { closest->t, v };
    }



    void PhotonmapRender::emitPhotons(int numPhotons)
    {
        //在光源上进行随机采样。
        auto light = scene.areaLightBuffer[0];
        int lightSample = 100;
        for (int i = 0; i < lightSample; i++)
        {
            auto r = defaultSamplerInstance<UniformPositiveSquare>().sample2d();
            float rx = r.x;
            float ry = r.y;
            Vec3 samplePoint = light.position + rx * light.u + ry * light.v;
            for (int j = 0; j < numPhotons; j++)
            {
                Vec3 random = defaultSamplerInstance<HemiSphere>().sample3d();
                Vec3 radiance = light.radiance;
                //创建对应的光子
                Photon photon{samplePoint,random,radiance};
                buildPhotonMap(photon);
            }
        }
    }

    void PhotonmapRender::buildPhotonMap(Photon photon)
    {
        //将原有的光子包装成一束光
        Ray r{ photon.position,photon.direction };
        Vec3 curr_power = photon.power;
        //在场景中最多弹射5次
        int maxtrans = 5;
        for (int i = 0; i < maxtrans; i++)
        {
            //得到最先碰撞的物体
            auto hitObject = PhotonHit(r);
            if (hitObject)
            {
                auto mtlHandle = hitObject->material;
                //在这里只是调用了漫反射的处理函数
                auto scattered = shaderPrograms[mtlHandle.index()]->shade(r, hitObject->hitPoint, hitObject->normal);
                auto attenuation = scattered.attenuation;
                r = scattered.ray;
                photonMap.push_back({ r.origin,r.direction,curr_power * attenuation });
            }
            else
            {
                break;
            }
        }
    }

    HitRecord PhotonmapRender::PhotonHit(Ray r)
    {
        HitRecord closestHit = nullopt;
        float closest = FLOAT_INF;

        for (auto& s : scene.sphereBuffer) {
            auto hitRecord = Intersection::xSphere(r, s, 0.000001, closest);
            if (hitRecord && hitRecord->t < closest) {
                closest = hitRecord->t;
                closestHit = hitRecord;
            }
        }
        //遍历所有的三角面片
        for (auto& t : scene.triangleBuffer) {
            auto hitRecord = Intersection::xTriangle(r, t, 0.000001, closest);
            if (hitRecord && hitRecord->t < closest) {
                closest = hitRecord->t;
                closestHit = hitRecord;
            }
        }
        //遍历所有的平面
        for (auto& p : scene.planeBuffer) {
            auto hitRecord = Intersection::xPlane(r, p, 0.000001, closest);
            if (hitRecord && hitRecord->t < closest) {
                closest = hitRecord->t;
                closestHit = hitRecord;
            }
        }
        //返回最近的交点
        return closestHit;
    }

    Vec3 PhotonmapRender::traceRay(Ray r)
    {
        //当前光线最先碰撞到的物体
        auto hitObject = closestHitObject(r);
        if (hitObject)
        {
            Vec3 directColor= computeDirectLighting(hitObject);
            Vec3 indirectColor = computeIndirectLighting(hitObject);
            return directColor + indirectColor;
        }
        else
        {
            return scene.ambient.constant;
        }
    }

    Vec3 PhotonmapRender::computeDirectLighting(HitRecord hitObject)
    {
        Vec3 color{ 0,0,0 };
        for (auto& a : scene.areaLightBuffer)
        {
            Vec3 lightPos = a.position;
            Vec3 radiance = a.radiance;
            Vec3 lightDir = lightPos - hitObject->hitPoint;
            float lightDistance = glm::length(lightDir);
            lightDir = glm::normalize(lightDir);
            float kEpsilon = 1e-5;
            Ray shadowRay(hitObject->hitPoint + hitObject->normal * kEpsilon, lightDir);

            auto shadowhitObject = closestHitObject(shadowRay);
            auto [t, emitted] = closestHitLight(shadowRay);
            if (shadowhitObject&&shadowhitObject->t< lightDistance - kEpsilon)
            {
                continue;
            }
            float intensity = glm::dot(hitObject->normal, lightDir) / (lightDistance * lightDistance);
            //材质的反射率
            Vec3 materialColor = {0,0,0};
            Vec3 reflectedColor = radiance * materialColor * intensity;

            color += reflectedColor;
        }
        return color;
    }

    Vec3 PhotonmapRender::computeIndirectLighting(HitRecord hitObject)
    {
        return { 0,0,0 };
    }
}