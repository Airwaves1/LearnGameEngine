#include "Utils/Common.h"
#include "Renderer/RenderCommand.h"
#include  "Graphics/OpenGL/OpenGLRendererAPI.h"

namespace Airwave
{
    RendererAPI *RenderCommand::s_RendererAPI = new OpenGLRendererAPI();

    void RenderCommand::Init()
    {
        s_RendererAPI->Init();
    }

    // 调用此API之前, 绑定了什么Shader, 就用对应的Shader绘制这个vertex array
    void RenderCommand::DrwaIndexed(const std::shared_ptr<VertexArray> &va, uint32_t count)
    {
        // TODO: 为啥不绑定Vertex Buffer
        va->Bind();
        s_RendererAPI->DrawIndexed(va, count);
    }

    void RenderCommand::Clear()
    {
        s_RendererAPI->Clear();
    }

    void RenderCommand::SetClearColor(const glm::vec4 &color)
    {
        s_RendererAPI->SetClearColor(color);
    }

} // namespace Airwave
