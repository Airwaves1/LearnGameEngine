#ifndef SHADER_LIBRARY_H
#define SHADER_LIBRARY_H

#include "Utils/Common.h"
#include "Renderer/Shaders/Shader.h"

namespace Airwave
{
    class ShaderLibrary
    {
    public:
        ShaderLibrary() : m_Shaders() {}
        ~ShaderLibrary() = default;

        void Add(const std::string &name, const std::shared_ptr<Shader> &shader);
        void Add(const std::shared_ptr<Shader> &shader);

        std::shared_ptr<Shader> Load(const std::string &name,
                                     const std::string &vertex,
                                     const std::string &fragment,
                                     bool fromFile = true);
    
        std::shared_ptr<Shader> Load(const std::string &name, const std::string &filepath);

        std::shared_ptr<Shader> Get(const std::string &name);

        bool Exists(const std::string &name) const { 
            return m_Shaders.find(name) != m_Shaders.end(); 
        }

    private:
        std::unordered_map<std::string, std::shared_ptr<Shader>> m_Shaders;
    };
} // namespace Airwave

#endif // SHADER_LIBRARY_H