#include "Framebuffer.h"
#include "Renderer/Renderer.h"
#include "Graphics/OpenGL/OpenGLFramebuffer.h"

namespace Airwave
{
    std::shared_ptr<Framebuffer> Framebuffer::Create(uint32_t width, uint32_t height, FramebufferSpecification specification)
    {
        switch (Renderer::GetAPI())
        {
        case RendererAPI::APIType::None:
            AIRWAVE_ASSERT(false, "RendererAPI::None is currently not supported!");
            return nullptr;
            
        case RendererAPI::APIType::OpenGL:
            return std::make_shared<OpenGLFramebuffer>(width, height, specification);

        default:
            AIRWAVE_ASSERT(false, "Unknown RendererAPI!");
            return nullptr;
        }
    }
} // namespace Airwave
