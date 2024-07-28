#include <AirwaveEngine.h>
#include <imgui.h>
#include "Camera/OrthographicCamera.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

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
            layout(location = 1) in vec2 a_TexCoord;

            uniform mat4 u_ViewProjection;
            uniform mat4 u_Model;

            out vec2 v_TexCoord;

            void main()
            {
                gl_Position = u_ViewProjection * u_Model * vec4(a_Position, 1.0);
                
                v_TexCoord = a_TexCoord;
            }
        )";

        std::string fragmentShaderSource = R"(
            #version 330 core

            in vec2 v_TexCoord;

            uniform sampler2D u_Texture0;
            uniform sampler2D u_Texture1;

            out vec4 FragColor;

            void main()
            {
                vec4 texColor0 = texture(u_Texture0, v_TexCoord);
                vec4 texColor1 = texture(u_Texture1, v_TexCoord);

                FragColor = mix(texColor0, texColor1, 0.2);
            }
        )";

        // m_Shader.reset(Airwave::Shader::Create(vertexShaderSource, fragmentShaderSource, false));
        m_Shader.reset(Airwave::Shader::Create(ASSETS_SHADER_DIR "00/Texture.vert", ASSETS_SHADER_DIR "00/Texture.frag"));

        m_Texture0 = Airwave::Texture2D::CreateRef(ASSETS_TEXTURE_DIR "container2.png");
        m_Texture1 = Airwave::Texture2D::CreateRef(ASSETS_TEXTURE_DIR "awesomeface.png");
        
        m_Shader->Bind();
        m_Shader->UploadUniformInt("u_Texture0", 0);
        m_Shader->UploadUniformInt("u_Texture1", 1);

        float squareVertices[4 * 5] = {
            -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
            0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
            0.5f, 0.5f, 0.0f, 1.0f, 1.0f,
            -0.5f, 0.5f, 0.0f, 0.0f, 1.0f};

        uint32_t squareIndices[6] = {0, 1, 2, 2, 3, 0};

        m_SquareVertexArray.reset(Airwave::VertexArray::Create());
        m_SquareVertexArray->Bind();

        std::shared_ptr<Airwave::VertexBuffer> vb2;
        vb2.reset(Airwave::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
        Airwave::BufferLayout layout2 = {
            {Airwave::ShaderDataType::FLOAT3, "a_Position"},
            {Airwave::ShaderDataType::FLOAT2, "a_TexCoord"}};

        vb2->SetBufferLayout(layout2);

        m_SquareVertexArray->AddVertexBuffer(vb2);

        std::shared_ptr<Airwave::IndexBuffer> ib2;
        ib2.reset(Airwave::IndexBuffer::Create(squareIndices, sizeof(squareIndices)));
        m_SquareVertexArray->SetIndexBuffer(ib2);

        m_SquareVertexArray->Unbind();
    }

    void OnUpdate(float deltaTime) override
    {
        Airwave::RenderCommand::SetClearColor({0.5, 0.4, 0.7, 1.0});
        Airwave::RenderCommand::Clear();

        glm::vec3 scale = glm::vec3(0.2f);

        Airwave::Renderer::BeginScene(m_Camera.get());

        static int count = 10;
        for (int i = 0; i < count; i++)
        {
            for (int j = 0; j < count; j++)
            {
                glm::vec3 translate = glm::vec3(m_CameraPosition.x + i * 0.21f, m_CameraPosition.y + j * 0.21f, m_CameraPosition.z);
                glm::mat4 model = glm::translate(glm::mat4(1.0f), translate) * glm::scale(glm::mat4(1.0f), scale);
                m_Texture0->Bind(0);
                m_Texture1->Bind(1);
                Airwave::Renderer::Submit(m_Shader, m_SquareVertexArray, model);
                Airwave::Renderer::EndScene();
                Airwave::RenderCommand::DrwaIndexed(m_SquareVertexArray);
            }
        }
    }

    void OnEvent(Airwave::Event &event) override
    {
        Airwave::EventDispatcher dispatcher(event);
        dispatcher.Dispatch<Airwave::KeyPressedEvent>(BIND_EVENT_FN(ExampleLayer::OnKeyPressedEvent));
        dispatcher.Dispatch<Airwave::MouseScrolledEvent>(BIND_EVENT_FN(ExampleLayer::OnMouseScrolledEvent));
    }

    bool OnKeyPressedEvent(Airwave::KeyPressedEvent &event)
    {
        if (event.GetKeycode() == AW_KEY_LEFT)
        {
            m_CameraPosition.x -= m_CameraSpeed;
            return true;
        }
        if (event.GetKeycode() == AW_KEY_RIGHT)
        {
            m_CameraPosition.x += m_CameraSpeed;
            return true;
        }
        if (event.GetKeycode() == AW_KEY_UP)
        {
            m_CameraPosition.y += m_CameraSpeed;
            return true;
        }
        if (event.GetKeycode() == AW_KEY_DOWN)
        {
            m_CameraPosition.y -= m_CameraSpeed;
            return true;
        }
        return false;
    }

    bool OnMouseScrolledEvent(Airwave::MouseScrolledEvent &event)
    {
        // 滚轮移动相机的z轴, 实现缩放
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

    std::shared_ptr<Airwave::VertexArray> m_TriangleVertexArray;
    std::shared_ptr<Airwave::VertexArray> m_SquareVertexArray;
    std::shared_ptr<Airwave::Shader> m_Shader;

    std::shared_ptr<Airwave::Texture> m_Texture0;
    std::shared_ptr<Airwave::Texture> m_Texture1;
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
