#include "Renderer/Shaders/Shader.h"
#include "Utils/Common.h"

#include "Renderer/Renderer.h"
#include "Graphics/OpenGL/OpenGLShader.h"

namespace Airwave
{

    Shader* Shader::Create(const std::string &vertexSrc, const std::string &fragmentSrc, bool fromFile)
    {
        RendererAPI::APIType type = Renderer::GetAPI();
        switch (type)
        {
        case RendererAPI::APIType::None:
            LOG_ERROR("RendererAPI::None is not supported");
            return nullptr;
        case RendererAPI::APIType::OpenGL:
            return new OpenGLShader(vertexSrc, fragmentSrc, fromFile);
        default:
            LOG_ERROR("Unknown RendererAPI");
            return nullptr;
        }

        return nullptr;
    }
} // namespace Airwave