#include "server/Server.hpp"

#include "SimplePathTracer.hpp"

#include "VertexTransformer.hpp"
#include "intersections/intersections.hpp"

#include "glm/gtc/matrix_transform.hpp"

namespace SimplePathTracer
{
    RGB SimplePathTracerRenderer::gamma(const RGB& rgb) {
        return glm::sqrt(rgb);
    }

    void SimplePathTracerRenderer::renderTask(RGBA* pixels, int width, int height, int off, int step) {
        //off是偏移量，代表了从第几行开始进行渲染
        //step是每次渲染的行数
        for(int i=off; i<height; i+=step) {
            for (int j=0; j<width; j++) {
                Vec3 color{0, 0, 0};

                //samples是当前类中设定的采样次数
                for (int k=0; k < samples; k++) {

                    //在（-1，-1）至（1，1）中均匀分布的随机二维向量
                    auto r = defaultSamplerInstance<UniformInSquare>().sample2d();
                    float rx = r.x;
                    float ry = r.y;
                    float x = (float(j)+rx)/float(width);
                    float y = (float(i)+ry)/float(height);
                    auto ray = camera.shoot(x, y);
                    color += trace(ray, 0);
                }
                color /= samples;
                color = gamma(color);
                pixels[(height-i-1)*width+j] = {color, 1};
            }
        }
    }

    auto SimplePathTracerRenderer::render() -> RenderResult {
        // shaders
        shaderPrograms.clear();
        ShaderCreator shaderCreator{};
        for (auto& m : scene.materials) {
            shaderPrograms.push_back(shaderCreator.create(m, scene.textures));
        }

        RGBA* pixels = new RGBA[width*height]{};

        // 局部坐标转换成世界坐标
        VertexTransformer vertexTransformer{};
        vertexTransformer.exec(spScene);

        const auto taskNums = 8;
        thread t[taskNums];
        for (int i=0; i < taskNums; i++) {
            t[i] = thread(&SimplePathTracerRenderer::renderTask,
                this, pixels, width, height, i, taskNums);
        }
        for(int i=0; i < taskNums; i++) {
            t[i].join();
        }
        getServer().logger.log("Done...");
        return {pixels, width, height};
    }

    void SimplePathTracerRenderer::release(const RenderResult& r) {
        auto [p, w, h] = r;
        delete[] p;
    }

    //求解最近碰撞物体
    HitRecord SimplePathTracerRenderer::closestHitObject(const Ray& r) {
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
    tuple<float, Vec3> SimplePathTracerRenderer::closestHitLight(const Ray& r) {
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

    RGB SimplePathTracerRenderer::trace(const Ray& r, int currDepth) {
        //如果已经达到当前的最大深度，则直接返回当前的环境背景光
        if (currDepth == depth) return scene.ambient.constant;
        auto hitObject = closestHitObject(r);

        //找到与光线最近的光源的交点信息。获取距离和辐射强度
        auto [ t, emitted ] = closestHitLight(r);
        // hit object
        //是指先碰到了物体，后碰到了区域光源。
        if (hitObject && hitObject->t < t) {
            auto mtlHandle = hitObject->material;
            auto scattered = shaderPrograms[mtlHandle.index()]->shade(r, hitObject->hitPoint, hitObject->normal);
            auto scatteredRay = scattered.ray;
            auto attenuation = scattered.attenuation;
            auto emitted = scattered.emitted;
            auto next = trace(scatteredRay, currDepth+1);
            float n_dot_in = glm::dot(hitObject->normal, scatteredRay.direction);
            float pdf = scattered.pdf;
            /**
             * emitted      - Le(p, w_0)
             * next         - Li(p, w_i)
             * n_dot_in     - cos<n, w_i>
             * atteunation  - BRDF
             * pdf          - p(w)
             **/
            return emitted + attenuation * next * n_dot_in / pdf;
        }
        // 
        else if (t != FLOAT_INF) {
            return emitted;
        }
        else {
            return Vec3{0};
        }
    }
}