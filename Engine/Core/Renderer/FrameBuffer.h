#ifndef FRAME_BUFFER_H
#define FRAME_BUFFER_H

#include "Utils/Common.h"
#include "Renderer/Shader.h"

namespace Airwave
{

    struct FrameBufferSpecification
    {
        uint32_t width = 800;
        uint32_t height = 600;
        uint32_t colorAttachmentCount = 1;
        uint32_t depthAttachmentCount = 1;
        uint32_t stencilAttachmentCount = 0;
        uint32_t samples = 4;
        bool swapChainTarget = false;
        bool enableMSAA = false;
    };

    class FrameBuffer
    {
    public:
        static std::shared_ptr<FrameBuffer> Create(const FrameBufferSpecification &spec);
        FrameBuffer(uint32_t width, uint32_t height) : m_Width(width), m_Height(height) {}
        virtual ~FrameBuffer() {}

        virtual void Bind() = 0;
        virtual void Unbind() = 0;

        virtual void ResizeColorAttachment(uint32_t width, uint32_t height) = 0;
        virtual uint32_t GetColorAttachmentTextureId() = 0;
        virtual void SetColorAttachmentTextureId(uint32_t textureID, uint32_t value) = 0;
        virtual int ReadPixel(uint32_t attachmentIndex, int x, int y) = 0;

        virtual void SetShader(const std::shared_ptr<Shader> &shader) { m_Shader = shader; }
        virtual std::shared_ptr<Shader> GetShader() { return m_Shader; }
        

        virtual void SetUpMSAAContext() = 0;
        virtual void ResolveMSAAContext(uint32_t width, uint32_t height) = 0; 

        virtual const FrameBufferSpecification &GetSpecification() const = 0;


    protected:
        uint32_t m_Width = 800;
        uint32_t m_Height = 600;
        bool b_ShowOnScreen = false;
        std::shared_ptr<Shader> m_Shader;

    };

} // namespace Airwave

#endif // FRAME_BUFFER_H