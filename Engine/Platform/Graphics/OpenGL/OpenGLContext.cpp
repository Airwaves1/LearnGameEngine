#include "Graphics/OpenGL/OpenGLContext.h"

#include "Utils/Common.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Airwave
{
    OpenGLContext::OpenGLContext(GLFWwindow *windowHandle)
        : m_WindowHandle(windowHandle)
    {
        AIRWAVE_ASSERT(windowHandle, "Window handle is null!");
    }

    void OpenGLContext::Init()
    {
        glfwMakeContextCurrent(m_WindowHandle);
        if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            LOG_ERROR("Failed to initialize Glad!");
        }

        LOG_INFO("OpenGL Info:");
        std::string vendor = (char *)glGetString(GL_VENDOR);
        std::string renderer = (char *)glGetString(GL_RENDERER);
        std::string version = (char *)glGetString(GL_VERSION);

        LOG_INFO("  Vendor: {0}", vendor);
        LOG_INFO("  Renderer: {0}", renderer);
        LOG_INFO("  Version: {0}", version);

    }

    void OpenGLContext::SwapBuffers()
    {
        glfwSwapBuffers(m_WindowHandle);
    }


} // namespace Airwave