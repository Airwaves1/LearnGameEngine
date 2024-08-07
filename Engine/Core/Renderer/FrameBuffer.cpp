#include "Renderer/FrameBuffer.h"
#include "Renderer/RendererAPI.h"
#include "Graphics/OpenGL/OpenGLFrameBuffer.h"

namespace Airwave
{
    std::shared_ptr<FrameBuffer> FrameBuffer::Create(const FrameBufferSpecification &spec)
    {
        switch (RendererAPI::GetAPIType())
        {
        case RendererAPI::APIType::None:
        {
            LOG_ERROR("RendererAPI::None is currently not supported!");
            AIRWAVE_ASSERT(false, "RendererAPI::None is currently not supported!");
            break;
        }
        case RendererAPI::APIType::OpenGL:
        {
            return std::make_shared<OpenGLFrameBuffer>(spec);
        }
        default:
            break;
        }

        // return std::make_shared<OpenGLFrameBuffer>();
        return nullptr;
    }
}