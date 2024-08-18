#ifndef OPENGL_FRAMEBUFFER_H
#define OPENGL_FRAMEBUFFER_H

#include "Renderer/Buffers/Framebuffer.h"
#include "Graphics/OpenGL/OpenGLTexture.h"
#include <memory>

namespace Airwave
{
    class OpenGLFramebuffer : public Framebuffer
    {
    public:
        OpenGLFramebuffer(uint32_t width, uint32_t height, FramebufferSpecification specification);
        virtual ~OpenGLFramebuffer();

        void Invalidate();

        virtual void Bind() override;
        virtual void Unbind() override;

        virtual void Resize(uint32_t width, uint32_t height) override;
        virtual void SetMSAA(bool enable) override;

        virtual uint32_t GetFramebufferID() const override { return m_RendererID; }
        virtual std::vector<uint32_t> GetColorAttachmentIDs() const override { return m_ColorAttachmentIDs; }
        virtual uint32_t GetDepthAttachmentID() const override { return m_DepthAttachmentID; }
        virtual uint32_t GetStencilAttachmentID() const override { return m_StencilAttachmentID; }

        // 添加纹理附件
        void AttachColorTexture(uint32_t index, const std::shared_ptr<OpenGLTexture2D> &texture);
        void AttachDepthTexture(const std::shared_ptr<OpenGLTexture2D> &texture);
        void AttachStencilTexture(const std::shared_ptr<OpenGLTexture2D> &texture);

        // 将多重采样的纹理附件转换为普通纹理附件
        virtual void BlitMSAAToDefaultFramebuffer(const uint32_t resolveFramebufferID) const override;


        // 读取像素，获取单点颜色
        virtual uint32_t ReadPixel(uint32_t attachmentIndex, int x, int y) override;

        // 渲染到全屏四边形上
        virtual void RenderToFullScreenQuad(std::shared_ptr<Shader> shader) override;

    private:
        uint32_t m_RendererID {0};
        std::vector<uint32_t> m_ColorAttachmentIDs {};
        uint32_t m_ColorAttachmentID {0};
        uint32_t m_DepthAttachmentID {0};
        uint32_t m_StencilAttachmentID {0};

        uint32_t m_FullScreenQuadVAO {0};

    };
} // namespace Airwave

#endif // OPENGL_FRAMEBUFFER_H