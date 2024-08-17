#ifndef OPENGL_TEXTURE_H
#define OPENGL_TEXTURE_H

#include "Renderer/Textures/Texture2D.h"
#include <glad/glad.h>
namespace Airwave
{

    class OpenGLTexture2D : public Texture2D
    {
    public:
        OpenGLTexture2D(const std::string &path, const TextureSpecification &specification);

        OpenGLTexture2D(uint32_t width, uint32_t height, const TextureSpecification &specification);

        virtual ~OpenGLTexture2D();

        virtual void Bind(uint32_t slot = 0) const override;
        virtual void Unbind() const override;
        

        virtual void SetData(const void *data, uint32_t size) override;

        virtual std::shared_ptr<Texture> Clone() override;

        virtual uint32_t GetRendererID() const override { return m_RendererID; }

    private:
        GLenum TextureWrapModeToGL(TextureWrapMode mode);
        GLenum TextureFilterModeToGL(TextureFilterMode mode);
        GLenum TextureFormatToGL(TextureFormat format);
        GLenum TextureInternalFormatToGL(TextureInternalFormat format);

    private:
        uint32_t m_RendererID;
    };

} // namespace Airwave

#endif // OPENGL_TEXTURE_H