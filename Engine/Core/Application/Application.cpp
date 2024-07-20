#include "Application.h"

#include "Event/Event.h"
#include "Event/ApplicationEvent.h"
#include "Utils/Log.h"

#include <glad/glad.h>
#include <glfw/glfw3.h>
namespace Airwave
{
#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

    Application::Application()
    {
        m_Window = std::unique_ptr<Window>(Window::Create());
        m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));
    }

    Application::~Application()
    {
    }

    void Application::Run()
    {

        while (this->b_Running)
        {
            glClearColor(0.2f, 0.3f, 0.8f, 1);
            glClear(GL_COLOR_BUFFER_BIT);

            for (std::shared_ptr<Layer> layer : m_LayerStack)
                layer->OnUpdate();

            m_Window->OnUpdate();
        }
    }

    void Application::OnEvent(Event &e)
    {
        EventDispatcher dispatcher(e);

        //1. 当接受窗口来的Event时, 首先判断是否是窗口关闭的事件
		// Dispatch函数只有在Event类型跟模板T匹配时, 才响应事件
		// std::bind其实是把函数和对应的参数绑定的一起
        dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));

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