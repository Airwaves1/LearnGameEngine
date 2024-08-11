#ifndef TEXTURE_H
#define TEXTURE_H

#include "Renderer/Renderer.h"
#include "Graphics/OpenGL/OpenGLTexture.h"

namespace Airwave
{
    std::shared_ptr<Texture2D> Texture2D::Create(const std::string &path)
    {
        switch (Renderer::GetAPI())
        {
        case RendererAPI::APIType::None:
            AIRWAVE_ASSERT(false, "RendererAPI::None is currently not supported!");
            return nullptr;
        case RendererAPI::APIType::OpenGL:
            return std::make_shared<OpenGLTexture2D>(path);
        }

        AIRWAVE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }

} // namespace Airwave

#endif // TEXTURE_H