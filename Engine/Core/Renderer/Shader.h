#ifndef SHADER_H
#define SHADER_H

#include "Utils/Common.h"

namespace Airwave
{
    class Shader
    {
    public:
        Shader(const std::string& vertexShaderSource, const std::string& fragmentShaderSource);
        ~Shader();

        void Bind() const;
        void Unbind() const;
    private:
        uint32_t m_RendererID;
    };

} // namespace Airwave

#endif // SHADER_H