#ifndef Texture_H
#define Texture_H

#include "Utils/Common.h"

namespace Airwave
{
    enum class TextureWrapMode
    {
        REPEAT = 0,
        MIRRORED_REPEAT = 1,
        CLAMP_TO_EDGE = 2,
        CLAMP_TO_BORDER = 3
    };

    enum class TextureFilterMode
    {
        NEAREST = 0,
        LINEAR = 1
    };

    enum class TextureFormat
    {
        RGB = 0,
        RGBA = 1,
        DEPTH = 2,

    };

    enum class TextureInternalFormat
    {
        RGB8 = 0,
        RGBA8 = 1,
        RGB16F = 2,
        RGBA16F = 3,
        DEPTH_COMPONENT_24 = 4,
        DEPTH_COMPONENT_32F = 5
    };

    struct TextureSpecification
    {
        
        TextureWrapMode wrapS = TextureWrapMode::REPEAT;
        TextureWrapMode wrapT = TextureWrapMode::REPEAT;
        TextureFilterMode minFilter = TextureFilterMode::LINEAR;
        TextureFilterMode magFilter = TextureFilterMode::LINEAR;

        TextureFormat format = TextureFormat::RGBA;
        TextureInternalFormat internalFormat = TextureInternalFormat::RGBA8;
        
        bool generateMipmap = false;
        bool enableMSAA = false;

        TextureSpecification() = default;
    };

    class Texture
    {
    public:
        Texture() = default;
        virtual ~Texture() = default;

        // 禁止拷贝
        Texture(const Texture &other) = delete;
        Texture &operator=(const Texture &other) = delete;
        virtual std::shared_ptr<Texture> Clone() = 0;

        virtual uint32_t GetWidth() const { return m_Width; }
        virtual uint32_t GetHeight() const { return m_Height; }

        virtual void Bind(uint32_t slot = 0) const = 0;
        virtual void Unbind() const = 0;

        virtual void SetData(const void *data, uint32_t size) = 0;
        virtual uint32_t GetRendererID() const = 0;

        virtual const TextureSpecification &GetSpecification() { return m_Specification; }

    protected:
        uint32_t m_Width = 0;
        uint32_t m_Height = 0;
        std::string m_Path{};

        TextureSpecification m_Specification;
    };

} // namespace Airwave

#endif // Texture_H