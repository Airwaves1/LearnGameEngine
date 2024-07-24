#ifndef RENDERER_COMMAND_H
#define RENDERER_COMMAND_H

#include "Renderer/RendererAPI.h"

namespace Airwave
{
    class RenderCommand
    {
    public:
        static void Init();
        static void DrwaIndexed(const std::shared_ptr<VertexArray> &va, uint32_t count = 0);
        static void Clear();
        static void SetClearColor(const glm::vec4 &color);

    private:
        static Airwave::RendererAPI* s_RendererAPI;
    };

} // namespace Airwave

#endif // RENDERER_COMMAND_H