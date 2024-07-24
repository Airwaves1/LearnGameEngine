#include "Renderer/Shader.h"
#include "Utils/Common.h"

#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

namespace Airwave {

    Shader::Shader(const std::string& vertexShaderSource, const std::string& fragmentShaderSource)
    {
        uint32_t vertexShader = glCreateShader(GL_VERTEX_SHADER);
        const char* vertexShaderSourceCStr = vertexShaderSource.c_str();
        glShaderSource(vertexShader, 1, &vertexShaderSourceCStr, nullptr);
        glCompileShader(vertexShader);

        int success;
        char infoLog[512];
        glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
            LOG_ERROR("Vertex shader compilation failed: {0}", infoLog);
        }

        uint32_t fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        const char* fragmentShaderSourceCStr = fragmentShaderSource.c_str();
        glShaderSource(fragmentShader, 1, &fragmentShaderSourceCStr, nullptr);
        glCompileShader(fragmentShader);

        glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
            LOG_ERROR("Fragment shader compilation failed: {0}", infoLog);
        }

        m_RendererID = glCreateProgram();
        glAttachShader(m_RendererID, vertexShader);
        glAttachShader(m_RendererID, fragmentShader);
        glLinkProgram(m_RendererID);

        glGetProgramiv(m_RendererID, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(m_RendererID, 512, nullptr, infoLog);
            LOG_ERROR("Shader program linking failed: {0}", infoLog);
        }

        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
    }

    Shader::~Shader()
    {
        glDeleteProgram(m_RendererID);
    }

    void Shader::Bind() const
    {
        glUseProgram(m_RendererID);
    }

    void Shader::Unbind() const
    {
        glUseProgram(0);
    }

    void Shader::UploadUniformMat4(const std::string &name, const glm::mat4 &matrix)
    {
       GLint location =  glGetUniformLocation(m_RendererID, name.c_str());
         glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
    }
}   // namespace Airwave