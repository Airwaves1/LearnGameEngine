#ifndef Texture_H
#define Texture_H

#include "Utils/Common.h"

namespace Airwave
{
    class Texture
    {
    public:
        virtual ~Texture() = default;

        virtual uint32_t GetWidth() const = 0;
        virtual uint32_t GetHeight() const = 0;
        virtual void Bind(uint32_t slot = 0) const = 0;
    };

    class Texture2D : public Texture
    {
    public:
        static Texture2D* Create(const std::string& path);
        static std::shared_ptr<Texture2D> CreateRef(const std::string& path);
    };

} // namespace Airwave

#endif // Texture_H