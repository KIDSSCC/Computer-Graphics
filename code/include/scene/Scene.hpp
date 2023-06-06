#pragma once
#ifndef __NR_SCENE_HPP__
#define __NR_SCENE_HPP__

#include "Texture.hpp"
#include "Material.hpp"
#include "Model.hpp"
#include "Light.hpp"
#include "Camera.hpp"

namespace NRenderer
{
    struct RenderOption
    {
        unsigned int width;
        unsigned int height;
        unsigned int depth;
        unsigned int samplesPerPixel;
        RenderOption()
            : width             (500)
            , height            (500)
            , depth             (4)
            , samplesPerPixel   (16)
        {}
    };

    struct Ambient
    {
        enum class Type
        {
            CONSTANT, ENVIROMENT_MAP
        };
        Type type;
        Vec3 constant = {};
        Handle environmentMap = {};
    };
    //场景结构
    struct Scene
    {
        Camera camera;

        RenderOption renderOption;
        //环境光
        Ambient ambient;

        // buffers，材质与纹理
        vector<Material> materials;
        vector<Texture> textures;
        //模型和节点
        vector<Model> models;
        vector<Node> nodes;

        // object buffer
        vector<Sphere> sphereBuffer;
        vector<Triangle> triangleBuffer;
        vector<Plane> planeBuffer;
        vector<Mesh> meshBuffer;

        vector<Light> lights;
        // light buffer
        vector<PointLight> pointLightBuffer;
        vector<AreaLight> areaLightBuffer;          //面光源
        vector<DirectionalLight> directionalLightBuffer;
        vector<SpotLight> spotLightBuffer;
    };
    using SharedScene = shared_ptr<Scene>;
} // namespace NRenderer


#endif