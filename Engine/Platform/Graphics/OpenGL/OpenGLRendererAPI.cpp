#include "Graphics/OpenGL/OpenGLRendererAPI.h"
#include "Utils/Common.h"
#include <glad/glad.h>


namespace Airwave
{
    void OpenGLRendererAPI::Init() const
    {
        glEnable(GL_BLEND);
        glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ZERO);

        glEnable(GL_DEPTH_TEST);
        glEnable(GL_LESS);

    }       

    
    void OpenGLRendererAPI::Clear() const
    {
        // TODO: 后期添加flag
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    }

    void OpenGLRendererAPI::SetClearColor(const glm::vec4 &color) const
    {
        glClearColor(color.x, color.y, color.z, color.w);
    }

    void OpenGLRendererAPI::DrawIndexed(const std::shared_ptr<VertexArray> &va, uint32_t count) const
    {

        if(count == 0)
        {
            glDrawElements(GL_TRIANGLES, va->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
        }
        else
        {
            glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr);
        }
    }

} // namespace Airwave
