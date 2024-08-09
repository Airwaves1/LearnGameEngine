#include "Renderer/Renderer.h"
#include "Renderer/RenderCommand.h"

namespace Airwave
{

    Renderer::SceneData *Renderer::s_SceneData = new Renderer::SceneData(); 

    void Renderer::Init()
    {
        RenderCommand::Init();
    }

    void Renderer::BeginScene(std::shared_ptr<Camera> camera)
    {
        s_SceneData->ViewProjectionMatrix = camera->GetProjectionMatrix() * camera->GetViewMatrix();
    }

    void Renderer::EndScene()
    {
    }

    void Renderer::Submit(const std::shared_ptr<Shader> &shader, const std::shared_ptr<VertexArray> &va,
                          const glm::mat4 &transform)
    {
        shader->Bind();
        shader->UploadUniformMat4("u_ViewProjection", s_SceneData->ViewProjectionMatrix);
        shader->UploadUniformMat4("u_Model", transform);

        RenderCommand::DrwaIndexed(va);
    }

}