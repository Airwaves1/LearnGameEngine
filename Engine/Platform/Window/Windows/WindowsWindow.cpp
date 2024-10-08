#include "Window/Windows/WindowsWindow.h"
#include "Utils/Common.h"

#include "Event/ApplicationEvent.h"
#include "Event/KeyEvent.h"
#include "Event/MouseEvent.h"

#include <glfw/glfw3.h>
#include "Graphics/OpenGL/OpenGLContext.h"

namespace Airwave
{

    static bool s_GLFWInitialized = false;

    static void GLFWErrorCallback(int error, const char *description)
    {
        LOG_ERROR("GLFW Error ({0}): {1}", error, description);
    }

    WindowsWindow::WindowsWindow(uint32_t width, uint32_t height, const std::string &title)
    {
        Init(width, height, title);
    }

    WindowsWindow::~WindowsWindow()
    {
        Shutdown();
    }

    void WindowsWindow::Init(uint32_t width, uint32_t height, const std::string &title)
    {
        m_Data.Title = title;
        m_Data.Width = width;
        m_Data.Height = height;

        if (!s_GLFWInitialized)
        {
            int success = glfwInit();
            AIRWAVE_ASSERT(success, "Could not initialize GLFW!");

            s_GLFWInitialized = true;
        }

        m_Window = glfwCreateWindow((int)width, (int)height, title.c_str(), nullptr, nullptr);

        // 设置窗口居中
        GLFWmonitor *monitor = glfwGetPrimaryMonitor();
        const GLFWvidmode *mode = glfwGetVideoMode(monitor);
        glfwSetWindowPos(m_Window, (mode->width - m_Data.Width) / 2, (mode->height - m_Data.Height) / 2);

        glfwMakeContextCurrent(m_Window);
        glfwSetWindowUserPointer(m_Window, &m_Data);
        SetVSync(true);

        glfwWindowHint(GLFW_SAMPLES, 16);

        // Set GLFW callbacks
        glfwSetWindowSizeCallback(m_Window, [](GLFWwindow *window, int width, int height)
                                  {
                                      WindowData &data = *(WindowData *)glfwGetWindowUserPointer(window);
                                      data.Width = width;
                                      data.Height = height;

                                      WindowResizeEvent event(width, height);
                                      data.EventCallback(event);
                                  });

        glfwSetFramebufferSizeCallback(m_Window, [](GLFWwindow *window, int width, int height)
                                       {
                                           WindowData &data = *(WindowData *)glfwGetWindowUserPointer(window);
                                           data.Width = width;
                                           data.Height = height;
                                           glViewport(0, 0, width, height);
                                        //    WindowResizeEvent event(width, height);
                                        //    data.EventCallback(event);
                                           LOG_INFO("glfwSetFramebufferSizeCallback: width = {0}, height = {1}", width, height); });

        glfwSetWindowCloseCallback(m_Window, [](GLFWwindow *window)
                                   {
                WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
                WindowCloseEvent event;
                data.EventCallback(event); });

        glfwSetKeyCallback(m_Window, [](GLFWwindow *window, int key, int scancode, int action, int mods)
                           {
                WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
                switch (action)
                {
                case GLFW_PRESS:
                {
                    KeyPressedEvent event(key, 0);
                    data.EventCallback(event);
                    break;
                }
                case GLFW_RELEASE:
                {
                    KeyReleasedEvent event(key);
                    data.EventCallback(event);
                    break;
                }
                case GLFW_REPEAT:
                {
                    KeyPressedEvent event(key, 1);
                    data.EventCallback(event);
                    break;
                }
                default:
                    break;
                } });

        glfwSetCharCallback(m_Window, [](GLFWwindow *window, unsigned int keycode)
                            {
                                WindowData &data = *(WindowData *)glfwGetWindowUserPointer(window);
                                KeyTypedEvent event(keycode);
                                data.EventCallback(event); });

        glfwSetMouseButtonCallback(m_Window, [](GLFWwindow *window, int button, int action, int mods)
                                   {
                WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
                switch (action)
                {
                case GLFW_PRESS:
                {
                    MouseButtonPressedEvent event(button);
                    data.EventCallback(event);
                    break;
                }
                case GLFW_RELEASE:
                {
                    MouseButtonReleasedEvent event(button);
                    data.EventCallback(event);
                    break;
                }
                default:
                    break;
                } });

        glfwSetScrollCallback(m_Window, [](GLFWwindow *window, double xOffset, double yOffset)
                              {
                WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
                MouseScrolledEvent event((float)xOffset, (float)yOffset);
                data.EventCallback(event); });

        glfwSetCursorPosCallback(m_Window, [](GLFWwindow *window, double xPos, double yPos)
                                 {
                                     WindowData &data = *(WindowData *)glfwGetWindowUserPointer(window);
                                     MouseMovedEvent event((float)xPos, (float)yPos);
                                     data.EventCallback(event);
                                     // LOG_INFO("MouseMovedEvent: xPos = {0}, yPos = {1}", xPos, yPos);
                                 });

        // Set GLFW error callback
        glfwSetErrorCallback(GLFWErrorCallback);

        // Load OpenGL functions using Glad
        m_Context = new OpenGLContext(m_Window);
        m_Context->Init();
    }

    void WindowsWindow::Shutdown()
    {
        glfwDestroyWindow(m_Window);
    }

    void WindowsWindow::OnUpdate()
    {
        glfwPollEvents();
        m_Context->SwapBuffers();
    }

    void WindowsWindow::SetVSync(bool enabled)
    {
        if (enabled)
            glfwSwapInterval(1);
        else
            glfwSwapInterval(0);

        m_Data.VSync = enabled;
    }

    bool WindowsWindow::IsVSync() const
    {
        return m_Data.VSync;
    }

} // namespace Airwave
