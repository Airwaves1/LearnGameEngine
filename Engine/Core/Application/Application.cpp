#include "Application.h"

#include "Event/Event.h"
#include "Event/ApplicationEvent.h"

#include "Renderer/Renderer.h"

#include "Utils/Log.h"

#include <glad/glad.h>

namespace Airwave
{
    Application *Application::s_Instance = nullptr;

    Application &Application::Get()
    {
        AIRWAVE_ASSERT(s_Instance, "Application is not created!");
        return *s_Instance;
    }

    void Application::Start(int argc, char *argv[])
    {
        // 1. 解析命令行参数
        ParseArguments(argc, argv);

        // 2. 日志系统初始化
        Airwave::Log::Init();

        // 3. 配置Application
        AIRWAVE_ASSERT(!s_Instance, "Application already exists!");
        s_Instance = this;
        OnConfiguration(&m_AppSettings);

        // 4. 创建Window
        m_Window = std::unique_ptr<Window>(Window::Create(m_AppSettings.width, m_AppSettings.height, m_AppSettings.title));
        m_Window->SetEventCallback(std::bind(&Application::OnEvent, this, std::placeholders::_1));

        // 5. 初始化Renderer
        Renderer::Init();

        // 6. 创建ImGuiLayer
        m_ImGuiLayer = std::make_shared<ImGuiLayer>();
        m_LayerStack.PushOverlay(m_ImGuiLayer);

        // 7. 初始化Application
        OnInit();

        // 8. 记录程序开始时间点
        m_StartTimePoint = std::chrono::steady_clock::now();
    }

    void Application::Stop()
    {
        Close();
        OnDestory();
    }

    void Application::MainLoop()
    {
        m_LastTimePoint = std::chrono::steady_clock::now();

        while (this->b_Running)
        {
            if (b_Paused)
            {
                continue;
            }

            // ################## 计算DeltaTime ##################
            m_DeltaTime = std::chrono::duration<float>(std::chrono::steady_clock::now() - m_LastTimePoint).count();
            m_LastTimePoint = std::chrono::steady_clock::now();

            // ################## 渲染 ##################
            for (std::shared_ptr<Layer> layer : m_LayerStack)
            {
                if (layer->IsEnabled())
                {
                    layer->OnUpdate(m_DeltaTime);
                    layer->OnRender();
                }
            }

            // ################## ImGui ##################
            m_ImGuiLayer->Begin();
            for (std::shared_ptr<Layer> layer : m_LayerStack)
            {
                if (layer->IsEnabled())
                {
                    layer->OnImGuiRender(m_DeltaTime);
                }
            }
            m_ImGuiLayer->End();

            // ################## Window ##################
            m_Window->OnUpdate();
        }

        LOG_INFO("Application is closed!");
    }

    void Application::PushLayer(std::shared_ptr<Layer> layer)
    {
        m_LayerStack.PushLayer(layer);
        // layer->OnAttach();
    }

    std::shared_ptr<Layer> Application::PopLayer()
    {
        return m_LayerStack.PopLayer();
    }

    void Application::ParseArguments(int argc, char *argv[])
    {
    }

    void Application::OnEvent(Event &e)
    {
        EventDispatcher dispatcher(e);

        dispatcher.Dispatch<WindowCloseEvent>(std::bind(&Application::OnWindowClose, this, std::placeholders::_1));
        dispatcher.Dispatch<WindowResizeEvent>(std::bind(&Application::OnWindowResize, this, std::placeholders::_1));

        // 逆序遍历是为了让ImGuiLayer最先收到Event
        for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();)
        {
            if (e.IsHandled())
                break;
            if ((*--it)->IsEnabled())
                (*it)->OnEvent(e);
        }
    }

    bool Application::OnWindowClose(WindowCloseEvent &e)
    {
        this->b_Running = false;
        return true;
    }

    bool Application::OnWindowResize(WindowResizeEvent &e)
    {
        Renderer::OnViewportResize(e.GetWindowWidth(), e.GetWindowHeight());
        return false;
    }


} // namespace Airawve