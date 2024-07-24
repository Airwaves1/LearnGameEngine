#ifndef SHADER_H
#define SHADER_H

#include "Utils/Common.h"
#include <glm/glm.hpp>

namespace Airwave
{
    class Shader
    {
    public:
        Shader(const std::string& vertexShaderSource, const std::string& fragmentShaderSource);
        ~Shader();

        void Bind() const;
        void Unbind() const;

        void UploadUniformMat4(const std::string& name, const glm::mat4& matrix);
    private:
        uint32_t m_RendererID;
    };

} // namespace Airwave

#endif // SHADER_H