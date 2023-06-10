#pragma once
#ifndef __PHOTON_MAP_HPP__
#define __PHOTON_MAP_HPP__


#include "scene/Scene.hpp"
#include "Ray.hpp"
#include "Camera.hpp"
#include "intersections/HitRecord.hpp"

#include "shaders/ShaderCreator.hpp"
#include "shaders/Shader.hpp"
#include "Photon.hpp"

namespace Photonmap
{
	using namespace NRenderer;
	using namespace std;

	class PhotonmapRender
	{
	public:
		//要渲染的场景与要渲染场景的引用
		SharedScene spScene;
		Scene& scene;
		//宽，高，追踪深度，每个像素的采样次数
		unsigned int width;
		unsigned int height;
		unsigned int depth;
		unsigned int samples;

		//使用的相机参数
		using SCam = Photonmap::Camera;
		SCam camera;

		//渲染时使用的着色器程序
		vector<SharedShader> shaderPrograms;

		//全局光子图
		vector<Photon> photonMap;

		PhotonmapRender(SharedScene spScene)
			: spScene(spScene)
			, scene(*spScene)
			, camera(spScene->camera)
		{
			width = scene.renderOption.width;
			height = scene.renderOption.height;
			depth = scene.renderOption.depth;
			samples = scene.renderOption.samplesPerPixel;
		}
		~PhotonmapRender() = default;
		using RenderResult = tuple<RGBA*, unsigned int, unsigned int>;
		RenderResult render();
		void release(const RenderResult& r);

		//进行伽马矫正，使用了glm::sqrt
		RGB gamma(const RGB& rgb);

		//追踪光线
		RGB trace(const Ray& ray, int currDepth);

		//求解最近碰撞物体
		HitRecord closestHitObject(const Ray& r);

		tuple<float, Vec3> closestHitLight(const Ray& r);

		//发射光子
		void emitPhotons(int numPhotons);
		//构建光子图
		void buildPhotonMap(Photon photon);
		
		//光子与物体的碰撞
		HitRecord PhotonHit(Ray r);
		
		//根据光子映射图进行渲染
		void renderTask(RGBA* pixels, int width, int height, int off, int step);
		//光线的追踪
		Vec3 traceRay(Ray r);

		Vec3 computeDirectLighting(HitRecord h);
		Vec3 computeIndirectLighting(HitRecord h);
	};
}

#endif