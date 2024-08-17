#ifndef TEXTURE2D_H
#define TEXTURE2D_H

#include "Renderer/Textures/Texture.h"

namespace Airwave
{
    class Texture2D : public Texture
    {
    public:
        // 从文件中加载纹理
        static std::shared_ptr<Texture2D> Create(const std::string &path, const TextureSpecification &specification = TextureSpecification());

        // 创建空白纹理
        static std::shared_ptr<Texture2D> Create(uint32_t width, uint32_t height, const TextureSpecification &specification = TextureSpecification());
        
    };



} // namespace Airwave



#endif // TEXTURE2D_H