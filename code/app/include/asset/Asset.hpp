#pragma once
#ifndef __NR_ASSET_HPP__
#define __NR_ASSET_HPP__

#include "common/macros.hpp"

#include "ModelItem.hpp"
#include "MaterialItem.hpp"
#include "TextureItem.hpp"
#include "LightItem.hpp"

namespace NRenderer
{
    struct Asset
    {
        // 模型，节点，材质，纹理，灯光
        vector<ModelItem> modelItems;
        vector<NodeItem> nodeItems;
        vector<MaterialItem> materialItems;
        vector<TextureItem> textureItems;
        vector<LightItem> lightItems;

        //所有的球体，三角形，平面，网格
        vector<SharedSphere> spheres;
        vector<SharedTriangle> triangles;
        vector<SharedPlane> planes;
        vector<SharedMesh> meshes;

        //点光源，面光源，定向光源，聚光灯
        vector<SharedPointLight> pointLights;
        vector<SharedAreaLight> areaLights;
        vector<SharedDirectionalLight> directionalLights;
        vector<SharedSpotLight> spotLights;

        //删除模型
        void clearModel() {
            for (auto& node : nodeItems) {
                if (node.glVAO != 0) {
                    glDeleteVertexArrays(1, &node.glVAO);
                }
                if (node.glVBO != 0) {
                    glDeleteBuffers(1, &node.glVBO);
                }
                if (node.glEBO != 0) {
                    glDeleteBuffers(1, &node.glEBO);
                }
            }
            for (auto& light : lightItems) {
                if (light.glVAO != 0) {
                    glDeleteVertexArrays(1, &light.glVAO);
                    light.glVAO = 0;
                }
                if (light.glVBO != 0) {
                    glDeleteBuffers(1, &light.glVBO);
                    light.glVBO = 0;
                }
                if (light.glEBO != 0) {
                    glDeleteBuffers(1, &light.glEBO);
                    light.glEBO = 0;
                }
            }
            modelItems.clear();
            nodeItems.clear();

            spheres.clear();
            triangles.clear();
            planes.clear();
            meshes.clear();

        }

        void clearLight() {
            lightItems.clear();

            pointLights.clear();
            areaLights.clear();
            directionalLights.clear();
            spotLights.clear();
        }

        void clearMaterial() {
            materialItems.clear();
        }

        void clearTexture() {
            textureItems.clear();
        }

        //生成预览OpenGL缓冲区
        void genPreviewGlBuffersPerNode(NodeItem& node);
        void genPreviewGlBuffersPerLight(LightItem& light);

        //更新节点和灯光缓冲区
        void updateNodeGlDrawData(NodeItem& node);
        void updateLightGlDrawData(LightItem& light);
    };
    
} // namespace NRenderer


#endif