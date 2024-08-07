#include "Graphics/OpenGL/OpenGLFrameBuffer.h"
#include "Graphics/OpenGL/OpenGLShader.h"
#include "Utils/Common.h"

namespace Airwave
{
    OpenGLFrameBuffer::OpenGLFrameBuffer(const FrameBufferSpecification &spec)
        : FrameBuffer(spec.width, spec.height)
    {
        // 创建帧缓冲对象
        glGenFramebuffers(1, &m_FramebufferId);
        glBindFramebuffer(GL_FRAMEBUFFER, m_FramebufferId);

        // 设置是否需要开启多重采样
        b_EnableMSAA = spec.enableMSAA;

        if (!b_EnableMSAA)
        { // 如果不适用MSAA，使用普通纹理附件

            for (uint32_t i = 0; i < spec.colorAttachmentCount; i++)
            {
                GLuint textureId;
                glGenTextures(1, &textureId);
                glBindTexture(GL_TEXTURE_2D, textureId);

                // 设置纹理格式
                if (i == 0)
                    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, spec.width, spec.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
                else
                    glTexImage2D(GL_TEXTURE_2D, 0, GL_R32I, spec.width, spec.height, 0, GL_RED_INTEGER, GL_UNSIGNED_BYTE, NULL);

                // 设置纹理参数
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

                // 将当前纹理附件附加到帧缓冲对象的颜色附件上
                glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, GL_TEXTURE_2D, textureId, 0);

                m_ColorAttachmentTexIndices.push_back(textureId);
            }

            // 创建深度和模板缓冲区
            for (uint32_t i = 0; i < spec.depthAttachmentCount; i++)
            {
                GLuint rbo;
                glGenRenderbuffers(1, &rbo);
                glBindRenderbuffer(GL_RENDERBUFFER, rbo);
                // use a single renderbuffer object for both a depth AND stencil buffer.
                glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, spec.width, spec.height);
                glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);
                m_RboAttachmentIndices.push_back(rbo);
            }
        }
        else // 如果启用MSAA，则使用多重采样纹理附件
        {
            for (uint32_t i = 0; i < spec.colorAttachmentCount; i++)
            {
                GLuint textureId;
                glGenTextures(1, &textureId);
                glBindTexture(GL_TEXTURE_2D, textureId);
                glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, spec.samples, GL_RGBA, spec.width, spec.height, GL_TRUE);
                glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, GL_TEXTURE_2D_MULTISAMPLE, textureId, 0);

                // 使用-1来作为占位符，表示这些颜色附件在MSAA模式下暂时没有有效的纹理ID，
                // 实际的纹理 ID 可能会在帧缓冲的解析阶段或其他处理阶段更新，以便正确使用和访问这些多重采样纹理
                m_ColorAttachmentTexIndices.push_back(-1);
            }

            for (uint32_t i = 0; i < spec.depthAttachmentCount; i++)
            {
                GLuint rbo;
                glGenRenderbuffers(1, &rbo);
                glBindRenderbuffer(GL_RENDERBUFFER, rbo);
                glRenderbufferStorageMultisample(GL_RENDERBUFFER, spec.samples, GL_DEPTH24_STENCIL8, spec.width, spec.height);
                glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);
                m_RboAttachmentIndices.push_back(rbo);
            }
        }

        // 检查帧缓冲是否完整
        if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        {
            LOG_ERROR("Framebuffer is not complete!");
            glBindFramebuffer(GL_FRAMEBUFFER, 0);
            return;
        }

        glBindFramebuffer(GL_FRAMEBUFFER, m_FramebufferId);

        const GLenum buffers[]{GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1};
        // 这个函数指定了用于渲染的颜色附件。
        // 它将 buffers 数组中的附件设置为当前帧缓冲对象的绘制目标。数组中的每个附件都将被渲染操作所使用
        glDrawBuffers(2, buffers);
    }

    OpenGLFrameBuffer::~OpenGLFrameBuffer()
    {

        for (GLuint textureId : m_ColorAttachmentTexIndices)
        {
            glDeleteTextures(1, &textureId);
        }

        for (GLuint rboId : m_RboAttachmentIndices)
        {
            glDeleteRenderbuffers(1, &rboId);
        }

        glDeleteFramebuffers(1, &m_FramebufferId);
    }

    GLuint OpenGLFrameBuffer::GetColorAttachmentId(uint32_t id)
    {
        return m_ColorAttachmentTexIndices[id];
    }

    void OpenGLFrameBuffer::Bind() 
    {
        glBindFramebuffer(GL_FRAMEBUFFER, m_FramebufferId);
        glViewport(0, 0, m_Width, m_Height);
    }

    void OpenGLFrameBuffer::Unbind() 
    {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    uint32_t OpenGLFrameBuffer::GetColorAttachmentTextureId()
    {
        if (b_EnableMSAA)
        {
            // TODO
            //  OpenGLShader* glShader = GetOpenGLShader(); // 获取当前的OpenGLShader
            //  if(glShader)
            //  {
            //      // 如果当前的OpenGLShader存在，则获取当前的OpenGLShader的MSAA纹理ID
            //      return glShader->GetMSAAColorAttachmentTextureId();
            //  }
        }

        return m_ColorAttachmentTexIndices[0]; // 或者其他默认值
    }

    void OpenGLFrameBuffer::ResizeColorAttachment(uint32_t width, uint32_t height)
    {
        if (m_FramebufferId != -1)
        {
            m_Width = width;
            m_Height = height;
            glBindTexture(GL_TEXTURE_2D, m_ColorAttachmentTexIndices[0]);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
        }
    }

    int OpenGLFrameBuffer::ReadPixel(uint32_t attachmentIndex, int x, int y)
    {
        if (b_EnableMSAA)
        {
            // TODO
        }
        this->Bind();
        glReadBuffer(GL_COLOR_ATTACHMENT0 + attachmentIndex);
        int pixelData;
        glReadPixels(x, y, 1, 1, GL_RED_INTEGER, GL_INT, &pixelData);
        this->Unbind();
        return pixelData;
    }

    void OpenGLFrameBuffer::SetColorAttachmentTextureId(uint32_t textureID, uint32_t value)
    {
        m_ColorAttachmentTexIndices[value] = textureID;
    }

    void OpenGLFrameBuffer::SetUpMSAAContext()
    {
        b_EnableMSAA = true;
        // TODO
    }

    void OpenGLFrameBuffer::ResolveMSAAContext(uint32_t width, uint32_t height)
    {
        if (b_EnableMSAA)
        {
            glBindFramebuffer(GL_READ_FRAMEBUFFER, m_FramebufferId);
            glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_FramebufferTempId);
            glBlitFramebuffer(0, 0, m_Width, m_Height, 0, 0, width, height, GL_COLOR_BUFFER_BIT, GL_NEAREST);
            glBindFramebuffer(GL_FRAMEBUFFER, m_FramebufferTempId);
        }
        else
        {
            LOG_WARN("MSAA is not enabled, no need to resolve MSAA context");
        }
    }

    OpenGLShader *OpenGLFrameBuffer::GetOpenGLShader()
    {
        return (OpenGLShader*)(&*(GetShader()));
    }

}