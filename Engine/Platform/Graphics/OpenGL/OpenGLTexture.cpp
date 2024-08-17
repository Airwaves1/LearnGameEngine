#include "OpenGLTexture.h"
#include "Graphics/OpenGL/OpenGLTexture.h"
#include "Utils/Common.h"
#include <stb_image/stb_image.h>
namespace Airwave
{
    OpenGLTexture2D::OpenGLTexture2D(const std::string &path, const TextureSpecification &specification)
    {
        int width, height, channels;
        stbi_set_flip_vertically_on_load(1);
        stbi_uc *data = stbi_load(path.c_str(), &width, &height, &channels, 0);
        AIRWAVE_ASSERT(data, "Failed to load image!");

        m_Path = path;
        m_Specification = specification;

        m_Width = width;
        m_Height = height;

        if (channels == 3)
        {
            m_Specification.format = TextureFormat::RGB;
            m_Specification.internalFormat = TextureInternalFormat::RGB8;
        }
        else if (channels == 4)
        {
            m_Specification.format = TextureFormat::RGBA;
            m_Specification.internalFormat = TextureInternalFormat::RGBA8;
        }

        GLenum internalFormat = TextureInternalFormatToGL(m_Specification.internalFormat);
        GLenum dataFormat = TextureFormatToGL(m_Specification.format);

        glGenTextures(1, &m_RendererID);
        glBindTexture(GL_TEXTURE_2D, m_RendererID);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

        glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, dataFormat, GL_UNSIGNED_BYTE, data);

        if (m_Specification.generateMipmap)
        {
            glGenerateMipmap(GL_TEXTURE_2D);
        }

        glBindTexture(GL_TEXTURE_2D, 0);

        stbi_image_free(data);
    }

    OpenGLTexture2D::OpenGLTexture2D(uint32_t width, uint32_t height, const TextureSpecification &specification)
    {
        m_Width = width;
        m_Height = height;
        m_Specification = specification;

        glGenTextures(1, &m_RendererID);
        glBindTexture(GL_TEXTURE_2D, m_RendererID);

        GLenum internalFormat = TextureInternalFormatToGL(m_Specification.internalFormat);
        GLenum dataFormat = TextureFormatToGL(m_Specification.format);

        if (m_Specification.enableMSAA)
        {
            glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, 4, internalFormat, m_Width, m_Height, GL_TRUE);
        }
        else
        {
            glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, m_Width, m_Height, 0, dataFormat, GL_UNSIGNED_BYTE, nullptr);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, TextureFilterModeToGL(m_Specification.minFilter));
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, TextureFilterModeToGL(m_Specification.magFilter));
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, TextureWrapModeToGL(m_Specification.wrapS));
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, TextureWrapModeToGL(m_Specification.wrapT));
            if (m_Specification.generateMipmap)
            {
                glGenerateMipmap(GL_TEXTURE_2D);

                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
            }
        }

        glBindTexture(GL_TEXTURE_2D, 0);
    }

    OpenGLTexture2D::~OpenGLTexture2D()
    {
        glDeleteTextures(1, &m_RendererID);
    }

    void OpenGLTexture2D::Bind(uint32_t slot) const
    {
        glActiveTexture(GL_TEXTURE0 + slot);
        glBindTexture(GL_TEXTURE_2D, m_RendererID);
    }

    void OpenGLTexture2D::Unbind() const
    {
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    void OpenGLTexture2D::SetData(const void *data, uint32_t size)
    {
        glBindTexture(GL_TEXTURE_2D, m_RendererID);

        GLenum internalFormat = TextureInternalFormatToGL(m_Specification.internalFormat);
        GLenum dataFormat = TextureFormatToGL(m_Specification.format);

        glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, m_Width, m_Height, 0, dataFormat, GL_UNSIGNED_BYTE, data);

        if (m_Specification.generateMipmap)
        {
            glGenerateMipmap(GL_TEXTURE_2D);
        }

        glBindTexture(GL_TEXTURE_2D, 0);
    }

    std::shared_ptr<Texture> OpenGLTexture2D::Clone()
    {
        if (m_Path.empty())
        {
            return std::make_shared<OpenGLTexture2D>(m_Width, m_Height, m_Specification);
        }
        else
        {
            return std::make_shared<OpenGLTexture2D>(m_Path, m_Specification);
        }
    }

    GLenum OpenGLTexture2D::TextureWrapModeToGL(TextureWrapMode mode)
    {
        switch (mode)
        {
        case TextureWrapMode::REPEAT:
            return GL_REPEAT;
        case TextureWrapMode::MIRRORED_REPEAT:
            return GL_MIRRORED_REPEAT;
        case TextureWrapMode::CLAMP_TO_EDGE:
            return GL_CLAMP_TO_EDGE;
        case TextureWrapMode::CLAMP_TO_BORDER:
            return GL_CLAMP_TO_BORDER;
        default:
            AIRWAVE_ASSERT(false, "Unknown TextureWrapMode!");
            return 0;
        }
    }

    GLenum OpenGLTexture2D::TextureFilterModeToGL(TextureFilterMode mode)
    {
        switch (mode)
        {
        case TextureFilterMode::NEAREST:
            return GL_NEAREST;
        case TextureFilterMode::LINEAR:
            return GL_LINEAR;
        default:
            AIRWAVE_ASSERT(false, "Unknown TextureFilterMode!");
            return 0;
        }
    }

    GLenum OpenGLTexture2D::TextureFormatToGL(TextureFormat format)
    {
        switch (format)
        {
        case TextureFormat::RGB:
            return GL_RGB;
        case TextureFormat::RGBA:
            return GL_RGBA;
        case TextureFormat::DEPTH:
            return GL_DEPTH_COMPONENT;
        default:
            AIRWAVE_ASSERT(false, "Unknown TextureFormat!");
            return 0;
        }
    }

    GLenum OpenGLTexture2D::TextureInternalFormatToGL(TextureInternalFormat format)
    {
        switch (format)
        {
        case TextureInternalFormat::RGB8:
            return GL_RGB8;
        case TextureInternalFormat::RGBA8:
            return GL_RGBA8;
        case TextureInternalFormat::RGB16F:
            return GL_RGB16F;
        case TextureInternalFormat::RGBA16F:
            return GL_RGBA16F;
        case TextureInternalFormat::DEPTH_COMPONENT_24:
            return GL_DEPTH_COMPONENT24;
        case TextureInternalFormat::DEPTH_COMPONENT_32F:
            return GL_DEPTH_COMPONENT32F;
        default:
            AIRWAVE_ASSERT(false, "Unknown TextureInternalFormat!");
            return 0;
        }
    }
} // namespace Airwave
