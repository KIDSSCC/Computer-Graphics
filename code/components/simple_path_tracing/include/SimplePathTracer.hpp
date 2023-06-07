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
        //Ҫ��Ⱦ�ĳ�����Ҫ��Ⱦ����������
        SharedScene spScene;
        Scene& scene;

        //���ߣ�׷����ȣ�ÿ�����صĲ�������
        unsigned int width;
        unsigned int height;
        unsigned int depth;
        unsigned int samples;

        //ʹ�õ��������
        using SCam = SimplePathTracer::Camera;
        SCam camera;

        //��Ⱦʱʹ�õ���ɫ������
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

        //�������飬����
        using RenderResult = tuple<RGBA*, unsigned int, unsigned int>;
        RenderResult render();
        void release(const RenderResult& r);

    private:
        //ִ����Ⱦ����
        void renderTask(RGBA* pixels, int width, int height, int off, int step);

        //����٤�������ʹ����glm::sqrt
        RGB gamma(const RGB& rgb);

        //׷�ٹ���
        RGB trace(const Ray& ray, int currDepth);

        //��������ײ����
        HitRecord closestHitObject(const Ray& r);

        tuple<float, Vec3> closestHitLight(const Ray& r);
    };
}

#endif