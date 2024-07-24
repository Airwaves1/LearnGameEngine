#include <AirwaveEngine.h>
#include <imgui.h>
#include "Camera/OrthographicCamera.h"


class ExampleLayer : public Airwave::Layer
{
public:
    ExampleLayer()
        : Layer("Example")
    {
        m_Camera = std::make_unique<Airwave::OrthographicCamera>(-1.9f, 1.9f, -0.9f, 0.9f);

        std::string vertexShaderSource = R"(
            #version 330 core

            layout(location = 0) in vec3 a_Position;

            uniform mat4 u_ViewProjection;

            out vec3 vertexColor;

            void main()
            {
                vertexColor = a_Position + 0.5;

                gl_Position = u_ViewProjection * vec4(a_Position, 1.0);
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

        m_Shader = std::make_shared<Airwave::Shader> (vertexShaderSource, fragmentShaderSource);

        float vertices[3 * 7] = {
            -0.5f, -0.5f, 0.0f,
            0.5f, -0.5f, 0.0f,
            0.0f, 0.5f, 0.0f};

        uint32_t indices[3] = {0, 1, 2};

        m_VertexArray.reset(Airwave::VertexArray::Create());
        m_VertexArray->Bind();

        std::shared_ptr<Airwave::VertexBuffer> vb;
        vb.reset(Airwave::VertexBuffer::Create(vertices, sizeof(vertices)));
        Airwave::BufferLayout layout = {
            {Airwave::ShaderDataType::FLOAT3, "a_Position"}
        };
        vb->SetBufferLayout(layout);

        m_VertexArray->AddVertexBuffer(vb);

        std::shared_ptr<Airwave::IndexBuffer> ib;
        ib.reset(Airwave::IndexBuffer::Create(indices, sizeof(indices)));
        m_VertexArray->SetIndexBuffer(ib);

    }

    void OnUpdate(float deltaTime) override
    {
        LOG_DEBUG("ExampleLayer::Update {0}", deltaTime);

        Airwave::RenderCommand::SetClearColor({0.5, 0.4, 0.7, 1.0});
        Airwave::RenderCommand::Clear();

        m_Camera->SetPosition(m_CameraPosition);

        Airwave::Renderer::BeginScene(*m_Camera.get());
        Airwave::Renderer::Submit(m_Shader, m_VertexArray);
        Airwave::Renderer::EndScene();

        Airwave::RenderCommand::DrwaIndexed(m_VertexArray);

    }

    void OnEvent(Airwave::Event &event) override
    {
        Airwave::EventDispatcher dispatcher(event);
        dispatcher.Dispatch<Airwave::KeyPressedEvent>(BIND_EVENT_FN(ExampleLayer::OnKeyPressedEvent));
        dispatcher.Dispatch<Airwave::MouseScrolledEvent>(BIND_EVENT_FN(ExampleLayer::OnMouseScrolledEvent));
    }

    bool OnKeyPressedEvent(Airwave::KeyPressedEvent &event)
    {
        if(event.GetKeycode() == AW_KEY_LEFT){
            m_CameraPosition.x -= m_CameraSpeed;
            return true;
        }
        if(event.GetKeycode() == AW_KEY_RIGHT){
            m_CameraPosition.x += m_CameraSpeed;
            return true;
        }
        if(event.GetKeycode() == AW_KEY_UP){
            m_CameraPosition.y += m_CameraSpeed;
            return true;
        }
        if(event.GetKeycode() == AW_KEY_DOWN){
            m_CameraPosition.y -= m_CameraSpeed;
            return true;
        }
        return false;
    }

    bool OnMouseScrolledEvent(Airwave::MouseScrolledEvent &event)
    {
        //滚轮移动相机的z轴, 实现缩放
        m_CameraPosition.z += event.GetYOffset() * m_CameraSpeed;
        return true;
    }

    void OnImGuiRender(float deltaTime) override
    {
        ImGui::Begin("Test");
        ImGui::Text("Hello World!");
        ImGui::End();
    }

private:
    std::unique_ptr<Airwave::Camera> m_Camera;
    glm::vec3 m_CameraPosition = {0.0f, 0.0f, 0.0f};
    float m_CameraSpeed = 0.05f;

    std::shared_ptr<Airwave::VertexArray> m_VertexArray;
    std::shared_ptr<Airwave::Shader> m_Shader;

    
};

class Sandbox : public Airwave::Application
{
public:
    Sandbox()
    {
        PushLayer(std::make_shared<ExampleLayer>());
    }

    ~Sandbox()
    {
    }
};

Airwave::Application *Airwave::CreateApplication()
{
    return new Sandbox();
}
