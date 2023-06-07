#pragma once
#ifndef __SIMPLE_PATH_TRACER_HPP__
#define __SIMPLE_PATH_TRACER_HPP__

#include "scene/Scene.hpp"
#include "Ray.hpp"
#include "Camera.hpp"
#include "intersections/HitRecord.hpp"

#include "shaders/ShaderCreator.hpp"

#include <tuple>
namespace SimplePathTracer
{
    using namespace NRenderer;
    using namespace std;

    class SimplePathTracerRenderer
    {
    public:
    private:
        //要渲染的场景与要渲染场景的引用
        SharedScene spScene;
        Scene& scene;

        //宽，高，追踪深度，每个像素的采样次数
        unsigned int width;
        unsigned int height;
        unsigned int depth;
        unsigned int samples;

        //使用的相机参数
        using SCam = SimplePathTracer::Camera;
        SCam camera;

        //渲染时使用的着色器程序
        vector<SharedShader> shaderPrograms;
    public:
        SimplePathTracerRenderer(SharedScene spScene)
            : spScene               (spScene)
            , scene                 (*spScene)
            , camera                (spScene->camera)
        {
            width = scene.renderOption.width;
            height = scene.renderOption.height;
            depth = scene.renderOption.depth;
            samples = scene.renderOption.samplesPerPixel;
        }
        ~SimplePathTracerRenderer() = default;

        //像素数组，宽，高
        using RenderResult = tuple<RGBA*, unsigned int, unsigned int>;
        RenderResult render();
        void release(const RenderResult& r);

    private:
        //执行渲染任务，
        void renderTask(RGBA* pixels, int width, int height, int off, int step);

        //进行伽马矫正，使用了glm::sqrt
        RGB gamma(const RGB& rgb);

        //追踪光纤
        RGB trace(const Ray& ray, int currDepth);

        //求解最近碰撞物体
        HitRecord closestHitObject(const Ray& r);

        tuple<float, Vec3> closestHitLight(const Ray& r);
    };
}

#endif