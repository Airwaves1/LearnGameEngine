#ifndef OPENGL_RENDERER_API_H
#define OPENGL_RENDERER_API_H

#include "Renderer/RendererAPI.h"

namespace Airwave
{
    class OpenGLRendererAPI : public RendererAPI
    {
    public:
        virtual void Init() const override;

        virtual void Clear() const override;

        virtual void SetClearColor(const glm::vec4 &color) const override;
        
        virtual void DrawIndexed(const std::shared_ptr<VertexArray> &va, uint32_t count = 0) const override;
    };
} // namespace Airwave

#endif // OPENGL_RENDERER_API_H