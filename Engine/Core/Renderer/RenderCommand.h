#ifndef RENDERER_COMMAND_H
#define RENDERER_COMMAND_H

#include "Renderer/RendererAPI.h"

// 调用RendererAPI的接口，这里是一个Wrapper

namespace Airwave
{
    class RenderCommand
    {
    public:
        static void Init();


        static void DrwaIndexed(const std::shared_ptr<VertexArray> &va, uint32_t count = 0);
        static void Clear(RenderClearFlag flag = RenderClearFlag::Color | RenderClearFlag::Depth | RenderClearFlag::Stencil);
        static void SetClearColor(const glm::vec4 &color);

        static void Enable(RenderState state);
        static void Disable(RenderState state);



        static void OnViewportResize(uint32_t width, uint32_t height);

    private:
        static Airwave::RendererAPI* s_RendererAPI;
    };

} // namespace Airwave
 
#endif // RENDERER_COMMAND_H