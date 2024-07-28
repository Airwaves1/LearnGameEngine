#include "Renderer/Shader.h"
#include "Utils/Common.h"

#include "Renderer/Renderer.h"
#include "Graphics/OpenGL/OpenGLShader.h"

namespace Airwave
{

    Shader* Shader::Create(const std::string &vertexSrc, const std::string &fragmentSrc)
    {
        RendererAPI::APIType type = Renderer::GetAPI();
        switch (type)
        {
        case RendererAPI::APIType::None:
            LOG_ERROR("RendererAPI::None is not supported");
            return nullptr;
        case RendererAPI::APIType::OpenGL:
            return new OpenGLShader(vertexSrc, fragmentSrc);
        default:
            LOG_ERROR("Unknown RendererAPI");
            return nullptr;
        }

        return nullptr;
    }

    Shader* Shader::Create(const std::string &path)
    {
        RendererAPI::APIType type = Renderer::GetAPI();
        switch (type)
        {
        case RendererAPI::APIType::None:
            LOG_ERROR("RendererAPI::None is not supported");
            return nullptr;
        case RendererAPI::APIType::OpenGL:
            return new OpenGLShader(path);
        default:
            LOG_ERROR("Unknown RendererAPI");
            return nullptr;
        }

        return nullptr;

    }
} // namespace Airwave