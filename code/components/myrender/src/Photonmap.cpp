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

    }

    auto PhotonmapRender::render() -> RenderResult {
        // shaders
        shaderPrograms.clear();
        ShaderCreator shaderCreator{};
        for (auto& m : scene.materials) {
            shaderPrograms.push_back(shaderCreator.create(m, scene.textures));
        }

        RGBA* pixels = new RGBA[width * height]{};

        // �ֲ�����ת������������
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

    void PhotonmapRender::emitPhotons(int numPhotons)
    {
        //�ڹ�Դ�Ͻ������������
        auto r = defaultSamplerInstance<UniformPostiveSquare>().sample2d();
    }
}