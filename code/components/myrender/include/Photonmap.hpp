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
		//Ҫ��Ⱦ�ĳ�����Ҫ��Ⱦ����������
		SharedScene spScene;
		Scene& scene;
		//���ߣ�׷����ȣ�ÿ�����صĲ�������
		unsigned int width;
		unsigned int height;
		unsigned int depth;
		unsigned int samples;

		//ʹ�õ��������
		using SCam = Photonmap::Camera;
		SCam camera;

		//��Ⱦʱʹ�õ���ɫ������
		vector<SharedShader> shaderPrograms;

		//ȫ�ֹ���ͼ
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

		//����٤�������ʹ����glm::sqrt
		RGB gamma(const RGB& rgb);

		//׷�ٹ���
		RGB trace(const Ray& ray, int currDepth);

		//��������ײ����
		HitRecord closestHitObject(const Ray& r);

		tuple<float, Vec3> closestHitLight(const Ray& r);

		//�������
		void emitPhotons(int numPhotons);
		//��������ͼ
		void buildPhotonMap(Photon photon);
		
		//�������������ײ
		HitRecord PhotonHit(Ray r);
		
		//���ݹ���ӳ��ͼ������Ⱦ
		void renderTask(RGBA* pixels, int width, int height, int off, int step);
		//���ߵ�׷��
		Vec3 traceRay(Ray r);

		Vec3 computeDirectLighting(HitRecord h);
		Vec3 computeIndirectLighting(HitRecord h);
	};
}

#endif