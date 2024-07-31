#include "Application.h"

#include "Event/Event.h"
#include "Event/ApplicationEvent.h"

#include "Renderer/Renderer.h"

#include "Utils/Log.h"

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
            m_DeltaTime = std::chrono::duration<float>(std::chrono::steady_clock::now() - m_LastTimePoint).count();
            m_LastTimePoint = std::chrono::steady_clock::now();

            for (std::shared_ptr<Layer> layer : m_LayerStack)
                layer->OnUpdate(m_DeltaTime);

            m_ImGuiLayer->Begin();
            for (std::shared_ptr<Layer> layer : m_LayerStack)
                layer->OnImGuiRender(m_DeltaTime);
            m_ImGuiLayer->End();

            m_Window->OnUpdate();
        }
    }

    void Application::OnEvent(Event &e)
    {
        EventDispatcher dispatcher(e);

        // 1. 当接受窗口来的Event时, 首先判断是否是窗口关闭的事件
        //  Dispatch函数只有在Event类型跟模板T匹配时, 才响应事件
        //  std::bind其实是把函数和对应的参数绑定的一起
        dispatcher.Dispatch<WindowCloseEvent>(std::bind(&Application::OnWindowClose, this, std::placeholders::_1));

        // 2. 否则才传递到layer来执行事件, 逆序遍历是为了让ImGuiLayer最先收到Event
        for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();)
        {
            (*--it)->OnEvent(e);
            if (e.IsHandled())
                break;
        }
    }

    void Application::PushLayer(std::shared_ptr<Layer> layer)
    {
        m_LayerStack.PushLayer(layer);
        layer->OnAttach();
    }

    std::shared_ptr<Layer> Application::PopLayer()
    {
        return m_LayerStack.PopLayer();
    }

    bool Application::OnWindowClose(WindowCloseEvent &e)
    {
        this->b_Running = false;
        return true;
    }

} // namespace Airawve