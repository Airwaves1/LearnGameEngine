#include "Application.h"

#include "Event/Event.h"
#include "Event/ApplicationEvent.h"
#include "Utils/Log.h"

#include <glad/glad.h>
#include <glfw/glfw3.h>

#include "Renderer/RendererAPI.h"
namespace Airwave
{
#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

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
        m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));

        // Application应该自带ImGuiLayer, 这段代码应该放到引擎内部而不是User的Application派生类里
        m_ImGuiLayer = std::make_shared<ImGuiLayer>();
        m_LayerStack.PushOverlay(m_ImGuiLayer);



        /*--------------------------------*/
        std::string vertexShaderSource = R"(
            #version 330 core
            layout(location = 0) in vec3 a_Position;
            out vec3 vertexColor;

            void main()
            {
                gl_Position = vec4(a_Position + 0.2, 1.0);
                vertexColor = a_Position + 0.5;
            }
        )";

        std::string fragmentShaderSource = R"(
            #version 330 core

            out vec4 FragColor;
            in vec3 vertexColor;
            
            void main()
            {
                FragColor = vec4(vertexColor, 1.0);
            }
        )";

        float vertices[3 * 7] = {
            -0.5f, -0.5f, 0.0f,
            0.5f, -0.5f, 0.0f,
            0.0f, 0.5f, 0.0f};

        uint32_t indices[3] = {0, 1, 2};

        // ----------------------------------
        m_Shader = std::make_unique<Shader>(vertexShaderSource, fragmentShaderSource);

        m_VertexArray.reset(VertexArray::Create());
        m_VertexArray->Bind();

        std::shared_ptr<VertexBuffer> vertexBuffer;
        vertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));
        BufferLayout layout = {
            {ShaderDataType::FLOAT3, "a_Position"}};
        vertexBuffer->SetBufferLayout(layout);

        m_VertexArray->AddVertexBuffer(vertexBuffer);

        std::shared_ptr<IndexBuffer> indexBuffer;
        indexBuffer.reset(IndexBuffer::Create(indices, sizeof(indices)));
        m_VertexArray->SetIndexBuffer(indexBuffer);



        // ----------------------------------
    }

    Application::~Application()
    {
    }

    void Application::Run()
    {

        while (this->b_Running)
        {
            glClearColor(0.5f, 0.3f, 0.8f, 1);
            glClear(GL_COLOR_BUFFER_BIT);

            m_Shader->Bind();
            m_VertexArray->Bind();
            glDrawElements(GL_TRIANGLES, m_VertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);

            for (std::shared_ptr<Layer> layer : m_LayerStack)
                layer->OnUpdate();

            m_ImGuiLayer->Begin();
            for (std::shared_ptr<Layer> layer : m_LayerStack)
                layer->OnImGuiRender();
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