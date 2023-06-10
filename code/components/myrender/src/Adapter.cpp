#include "component/RenderComponent.hpp"
#include "server/Server.hpp"
#include "component/RenderComponent.hpp"
#include "Camera.hpp"

#include "Photonmap.hpp"

using namespace std;
using namespace NRenderer;

namespace Photonmap
{
    using namespace std;
    using namespace NRenderer;

    // 继承RenderComponent, 复写render接口
    class Adapter : public RenderComponent
    {
        void render(SharedScene spScene) {
            PhotonmapRender renderer{ spScene };
            auto renderResult = renderer.render();
            auto [pixels, width, height] = renderResult;
            getServer().screen.set(pixels, width, height);
            renderer.release(renderResult);
        }
    };
}

// REGISTER_RENDERER(Name, Description, Class)
REGISTER_RENDERER(myrender, "own render test", Photonmap::Adapter);