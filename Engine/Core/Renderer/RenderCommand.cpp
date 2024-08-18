#include "Utils/Common.h"
#include "Renderer/RenderCommand.h"
#include "Graphics/OpenGL/OpenGLRendererAPI.h"
#include "RenderCommand.h"

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
        if (count == 0)
            s_RendererAPI->DrawIndexed(va, va->GetIndexBuffer()->GetCount());
        else
            s_RendererAPI->DrawIndexed(va, count); 
    }

    void RenderCommand::Clear(RenderClearFlag flag)
    {
        s_RendererAPI->Clear(flag);
    }

    void RenderCommand::SetClearColor(const glm::vec4 &color)
    {
        s_RendererAPI->SetClearColor(color);
    }

    void RenderCommand::Enable(RenderState state)
    {
        s_RendererAPI->Enable(state);
    }

    void RenderCommand::Disable(RenderState state)
    {
        s_RendererAPI->Disable(state);
    }

    void RenderCommand::OnViewportResize(uint32_t width, uint32_t height)
    {
        s_RendererAPI->OnViewportResize(width, height);
    }
}
