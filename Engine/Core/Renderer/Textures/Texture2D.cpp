#include "Texture2D.h"
#include "Renderer/Renderer.h"
#include "Graphics/OpenGL/OpenGLTexture.h"

namespace Airwave
{
    std::shared_ptr<Texture2D> Texture2D::Create(const std::string &path, const TextureSpecification &specification)
    {
        switch (Renderer::GetAPI())
        {
        case RendererAPI::APIType::None:
            AIRWAVE_ASSERT(false, "RendererAPI::None is currently not supported!");
            return nullptr;
        case RendererAPI::APIType::OpenGL:
            return std::make_shared<OpenGLTexture2D>(path, specification);
        }

        AIRWAVE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }

    std::shared_ptr<Texture2D> Texture2D::Create(uint32_t width, uint32_t height, const TextureSpecification &specification)
    {
        switch (Renderer::GetAPI())
        {
        case RendererAPI::APIType::None:
            AIRWAVE_ASSERT(false, "RendererAPI::None is currently not supported!");
            return nullptr;
        case RendererAPI::APIType::OpenGL:
            return std::make_shared<OpenGLTexture2D>(width, height, specification);
        }

        AIRWAVE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }

}
// namespace Airwave
