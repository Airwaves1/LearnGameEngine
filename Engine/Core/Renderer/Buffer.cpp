#include "Renderer/Buffer.h"

#include "Renderer/RendererAPI.h"

#include "Graphics/OpenGL/OpenGLBuffer.h"

namespace Airwave
{
    // 注意声明为static的函数，在定义的时候不需要写static关键字
    // 而且这个Create函数是在基类定义的，因为创建的窗口对象应该包含多种平台的派生类对象，所以放到了基类里
    // 而且这个基类的cpp引用了相关的派生类的头文件
    std::shared_ptr<VertexBuffer> VertexBuffer::Create(float *vertices, uint32_t size)
    {
        std::shared_ptr<VertexBuffer> buffer = nullptr;
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
            buffer = std::make_shared<OpenGLVertexBuffer>(vertices, size);
            break;
        }

        default:
            AIRWAVE_ASSERT(false, "Unknown RendererAPI");
            break;
        }

        return buffer;
    }

    std::shared_ptr<VertexBuffer> VertexBuffer::Create(uint32_t size)
    {
        std::shared_ptr<VertexBuffer> buffer = nullptr;
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
            buffer = std::make_shared<OpenGLVertexBuffer>(size);
            break;
        }

        default:
            AIRWAVE_ASSERT(false, "Unknown RendererAPI");
            break;
        }

        return buffer;
    }

    std::shared_ptr<IndexBuffer> IndexBuffer::Create(uint32_t *indices, uint32_t size)
    {
        std::shared_ptr<IndexBuffer> buffer = nullptr;
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
            buffer = std::make_shared<OpenGLIndexBuffer>(indices, size);
            break;
        }
        default:
            AIRWAVE_ASSERT(false, "Unknown RendererAPI");
            break;
        }

        return buffer;
    }

    void BufferLayout::CalculateElementsOffsets()
    {
        m_Stride = 0;
        for (auto &element : m_Elements)
        {
            element.SetOffset(m_Stride);
            m_Stride += element.GetSize();
            LOG_DEBUG("Element Offset: {0}, Element Size: {1}", element.GetOffset(), element.GetSize());
        }
    }

    bool BufferElement::IsIntergerType() const
    {
        if (m_Type == ShaderDataType::INT)
            return true;
        return false;
    }

} // namespace Airwave