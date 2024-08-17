#include "OpenGLFrameBuffer.h"
#include <glad/glad.h>
#include "Renderer/Buffers/FrameBuffer.h"
#include "Utils/Log.h"

namespace Airwave
{
    OpenGLFramebuffer::OpenGLFramebuffer(uint32_t width, uint32_t height, FramebufferSpecification specification)
    {
        m_Width = width;
        m_Height = height;
        m_Specification = specification;

        Invalidate();
    }

    OpenGLFramebuffer::~OpenGLFramebuffer()
    {
        if (m_RendererID)
        {
            glDeleteFramebuffers(1, &m_RendererID);
        }
        if (m_ColorAttachmentIDs.size())
        {
            glDeleteTextures(m_ColorAttachmentIDs.size(), m_ColorAttachmentIDs.data());
        }
        if (m_DepthAttachmentID)
        {
            glDeleteTextures(1, &m_DepthAttachmentID);
        }
        if (m_StencilAttachmentID)
        {
            glDeleteTextures(1, &m_StencilAttachmentID);
        }
    }
    void OpenGLFramebuffer::Invalidate()
    {
        if (m_RendererID)
        {
            glDeleteFramebuffers(1, &m_RendererID);
            m_RendererID = 0;
        }

        glGenFramebuffers(1, &m_RendererID);
        glBindFramebuffer(GL_FRAMEBUFFER, m_RendererID);

        // Color attachments
        m_ColorAttachmentIDs.resize(m_Specification.colorAttachmentCount);
        glGenTextures(m_Specification.colorAttachmentCount, m_ColorAttachmentIDs.data());
        for (uint32_t i = 0; i < m_Specification.colorAttachmentCount; i++)
        {
            if (m_Specification.enableMSAA)
            {
                glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, m_ColorAttachmentIDs[i]);
                glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, 4, GL_RGB, m_Width, m_Height, GL_TRUE);
                glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, 0);
                glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, GL_TEXTURE_2D_MULTISAMPLE, m_ColorAttachmentIDs[i], 0);
                LOG_DEBUG("Color Attachment ID: {}", m_ColorAttachmentIDs[i]);
            }
            else
            {
                glBindTexture(GL_TEXTURE_2D, m_ColorAttachmentIDs[i]);
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
                glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, GL_TEXTURE_2D, m_ColorAttachmentIDs[i], 0);
            }
        }

        // Depth attachment, 24 bits for depth and 8 bits for stencil
        uint32_t rbo;
        glGenRenderbuffers(1, &rbo);
        glBindRenderbuffer(GL_RENDERBUFFER, rbo);
        if (m_Specification.enableMSAA)
        {
            glRenderbufferStorageMultisample(GL_RENDERBUFFER, 4, GL_DEPTH24_STENCIL8, m_Width, m_Height);
        }
        else
        {
            glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, m_Width, m_Height);
        }
        glBindRenderbuffer(GL_RENDERBUFFER, 0);
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);

        GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
        if (status != GL_FRAMEBUFFER_COMPLETE)
        {
            LOG_ERROR("Framebuffer is incomplete! Status: {}", status);
        }

        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    void OpenGLFramebuffer::Bind()
    {
        glBindFramebuffer(GL_FRAMEBUFFER, m_RendererID);
    }

    void OpenGLFramebuffer::Unbind()
    {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    uint32_t OpenGLFramebuffer::ReadPixel(uint32_t attachmentIndex, int x, int y)
    {
        glBindFramebuffer(GL_FRAMEBUFFER, m_RendererID);
        glReadBuffer(GL_COLOR_ATTACHMENT0 + attachmentIndex);
        uint32_t pixelData;
        glReadPixels(x, y, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, &pixelData);
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        return pixelData;
    }

    void OpenGLFramebuffer::Resize(uint32_t width, uint32_t height)
    {
        if (m_Width == width && m_Height == height)
            return;

        m_Width = width;
        m_Height = height;
        Invalidate();
    }

    void OpenGLFramebuffer::SetMSAA(bool enable)
    {
        m_Specification.enableMSAA = enable;
        Invalidate();
    }

    void OpenGLFramebuffer::AttachColorTexture(uint32_t index, const std::shared_ptr<OpenGLTexture2D> &texture)
    {
        if (index >= m_ColorAttachmentIDs.size())
        {
            LOG_ERROR("Color attachment index out of range!");
            return;
        }

        glBindFramebuffer(GL_FRAMEBUFFER, m_RendererID);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + index, m_Specification.enableMSAA ? GL_TEXTURE_2D_MULTISAMPLE : GL_TEXTURE_2D, texture->GetRendererID(), 0);
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    void OpenGLFramebuffer::AttachDepthTexture(const std::shared_ptr<OpenGLTexture2D> &texture)
    {
        glBindFramebuffer(GL_FRAMEBUFFER, m_RendererID);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, texture->GetRendererID(), 0);
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    void OpenGLFramebuffer::AttachStencilTexture(const std::shared_ptr<OpenGLTexture2D> &texture)
    {
        glBindFramebuffer(GL_FRAMEBUFFER, m_RendererID);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_STENCIL_ATTACHMENT, GL_TEXTURE_2D, texture->GetRendererID(), 0);
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    void OpenGLFramebuffer::BlitMSAAToDefaultFramebuffer(const uint32_t resolveFramebufferID) const
    {
        glBindFramebuffer(GL_READ_FRAMEBUFFER, m_RendererID);
        glBindFramebuffer(GL_DRAW_FRAMEBUFFER, resolveFramebufferID);
        glBlitFramebuffer(0, 0, m_Width, m_Height, 0, 0, m_Width, m_Height, GL_COLOR_BUFFER_BIT, GL_NEAREST);
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

} // namespace Airwave
