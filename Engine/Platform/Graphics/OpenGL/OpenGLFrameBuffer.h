#ifndef OPENGL_FRAME_BUFFER_H
#define OPENGL_FRAME_BUFFER_H

#include "Renderer/FrameBuffer.h"
#include <glad/glad.h>
#include "Graphics/OpenGL/OpenGLShader.h"

namespace Airwave
{
    class OpenGLFrameBuffer : public FrameBuffer
    {
    public:
        // OpenGLFrameBuffer();
        OpenGLFrameBuffer(const FrameBufferSpecification &spec);
        ~OpenGLFrameBuffer() override;

        GLuint GetColorAttachmentId(uint32_t id);

        virtual uint32_t GetFrameBufferId() const { return m_FramebufferId; }

        virtual void Bind() override;
        virtual void Unbind() override;

        virtual void SetColorAttachmentTextureId(uint32_t textureID, uint32_t value) override;
        // 获取颜色附件的ID，返回的时void*类型，是为了兼容不同类型的纹理
        virtual uint32_t GetColorAttachmentTextureId() override;

        // 调整颜色附件的纹理大小，用于再帧缓冲尺寸发生变化时更新纹理大小
        virtual void ResizeColorAttachment(uint32_t width, uint32_t height) override;

        // 读取帧缓冲中特定位置的像素值，用于调试或者后期处理或者其他功能
        virtual int ReadPixel(uint32_t attachmentIndex, int x, int y) override;

        // 设置多重采用MSAA上下文，如果启用MSAA，则需要设置相应的帧缓冲或者纹理
        virtual void SetUpMSAAContext() override;

        // 解析MSAA纹理，将其内容从多重采样纹理复制到普通纹理
        virtual void ResolveMSAAContext(uint32_t width, uint32_t height) override;

        virtual const FrameBufferSpecification &GetSpecification() const override { return m_Specification; }

        // 获取OpenGLShader对象
        OpenGLShader *GetOpenGLShader();

    private:
    private:
        GLuint m_FramebufferId;

        // 临时帧缓冲和纹理的 ID
        GLuint m_FramebufferTempId;
        GLuint m_FramebufferTempTex;

        // 存储颜色附件纹理的ID
        std::vector<uint32_t> m_ColorAttachmentTexIndices;

        // 存储缓冲对象RBO的ID
        std::vector<int> m_RboAttachmentIndices;

        // 帧缓冲的规格
        FrameBufferSpecification m_Specification;

        // 是否启用多重采样

        bool b_EnableMSAA;
    };

} // namespace Airwave

#endif // OPENGL_FRAME_BUFFER_H