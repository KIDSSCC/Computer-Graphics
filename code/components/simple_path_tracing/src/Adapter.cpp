#include "server/Server.hpp"
#include "scene/Scene.hpp"
#include "component/RenderComponent.hpp"
#include "Camera.hpp"

#include "SimplePathTracer.hpp"
#include<iostream>

using namespace std;
using namespace NRenderer;

namespace SimplePathTracer
{
    class Adapter : public RenderComponent
    {
        void render(SharedScene spScene) {
            //创建一个SimplePathTracerRenderer对象，传入需要渲染的场景
            //通过render函数进行渲染，得到渲染结果
            SimplePathTracerRenderer renderer{spScene};
            auto renderResult = renderer.render();
            auto [ pixels, width, height ]  = renderResult;
            getServer().screen.set(pixels, width, height);
            renderer.release(renderResult);
        }
    };
}

const static string description = 
    "A Simple Path Tracer. "
    "Only some simple primitives and materials(Lambertian) are supported."
    "\nPlease use scene file : cornel_area_light.scn";

REGISTER_RENDERER(SimplePathTracer, description, SimplePathTracer::Adapter);