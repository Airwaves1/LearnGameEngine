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

    Application::Application()
    {
        // 日志系统初始化
        Airwave::Log::Init();

        AIRWAVE_ASSERT(!s_Instance, "Application already exists!");
        s_Instance = this;

        m_Window = std::unique_ptr<Window>(Window::Create());
        // 这里会设置m_Window里的std::function<void(Event&)>对象, 当接受Event时, 会调用Application::OnEvent函数
        m_Window->SetEventCallback(std::bind(&Application::OnEvent, this, std::placeholders::_1));

        Renderer::Init();

        // Application应该自带ImGuiLayer, 这段代码应该放到引擎内部而不是User的Application派生类里
        m_ImGuiLayer = std::make_shared<ImGuiLayer>();
        m_LayerStack.PushOverlay(m_ImGuiLayer);

        // 程序初始化完成后, 记录当前时间点为程序开始时间点
        m_StartTimePoint = std::chrono::steady_clock::now();
    }

    Application::~Application()
    {
    }

    void Application::Run()
    {
        m_LastTimePoint = std::chrono::steady_clock::now();

        while (this->b_Running)
        {
            if (b_Paused)
            {
                continue;
            }

            //################## 计算DeltaTime ##################
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
        if (e.GetWindowWidth() == 0 || e.GetWindowHeight() == 0)
        {
            this->b_Paused = true;
            return false;
        }
        this->b_Paused = false;
        Renderer::OnViewportResize(m_Window->GetWidth(), m_Window->GetHeight());
        return false;
    }

} // namespace Airawve