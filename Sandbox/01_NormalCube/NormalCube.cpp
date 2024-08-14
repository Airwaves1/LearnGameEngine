#include <AirwaveEngine.h>
#include <imgui.h>
// #include "Camera/OrthographicCamera.h"
#include "Camera/PerspectiveCamera.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Geometry/GeometryUtils.h"
#include "Renderer/Renderer.h"

#include <glad/glad.h>

class ExampleLayer : public Airwave::Layer
{
public:
    ExampleLayer()
        : Layer("Example")
    {
        auto width = Airwave::Application::Get().GetWindow().GetWidth();
        auto height = Airwave::Application::Get().GetWindow().GetWidth();

        m_Camera = std::make_shared<Airwave::PerspectiveCamera>(glm::radians(65.0f), width / height, 0.1f, 10000.0f);
        m_Camera->SetPosition({0.0f, 0.0f, 15.0f});

        m_ShaderLibrary = std::make_shared<Airwave::ShaderLibrary>();
        m_ShaderLibrary->Load("Texture", ASSETS_SHADER_DIR "00/Texture.vert", ASSETS_SHADER_DIR "00/Texture.frag");
        auto shader = m_ShaderLibrary->Load("Basic3D", ASSETS_SHADER_DIR "00/Basic3D.vert", ASSETS_SHADER_DIR "00/Basic3D.frag");

        glm::vec3 uniformColor = {0.8f, 0.3f, 0.6f};

        std::vector<Airwave::AWVertex> vertices;
        std::vector<uint32_t> indices;
        Airwave::GeometryUtils::CreateCube(vertices, indices, 1.0f, 1.0f, 1, 3, 3, 3);

        auto vertexData = Airwave::GeometryUtils::ConvertAWVertexToFloatArray(vertices);

        m_VertexArray = Airwave::VertexArray::Create();
        {
            auto vertexBuffer = Airwave::VertexBuffer::Create(vertexData.data(), vertexData.size() * sizeof(float));
            auto bufferLayout = Airwave::BufferLayout{
                {Airwave::ShaderDataType::FLOAT3, "a_Position"},
                {Airwave::ShaderDataType::FLOAT2, "a_TexCoord"},
                {Airwave::ShaderDataType::FLOAT3, "a_Normal"}};
            vertexBuffer->SetBufferLayout(bufferLayout);
            m_VertexArray->AddVertexBuffer(vertexBuffer);

            auto indexBuffer = Airwave::IndexBuffer::Create(indices.data(), indices.size() * sizeof(uint32_t));
            m_VertexArray->SetIndexBuffer(indexBuffer);
        }
        m_VertexArray->Unbind();
    }

    void OnUpdate(float deltaTime) override
    {
        Airwave::RenderCommand::SetClearColor({0.2, 0.2, 0.2, 1.0});
        Airwave::RenderCommand::Clear();

        float aspectRatio = (float)Airwave::Application::Get().GetWindow().GetWidth() / (float)Airwave::Application::Get().GetWindow().GetHeight();
        m_Camera->SetProjectionMatrix(glm::radians(65.0f), aspectRatio, 0.1f, 10000.0f);

        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, 0.0f, -10.0f));
        model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));
        model = glm::rotate(model, glm::radians(m_Rotation), glm::vec3(1.0f, 1.0f, 1.0f));
        m_Rotation += 15.0f * deltaTime;

        Airwave::Renderer::BeginScene(m_Camera);
        Airwave::Renderer::Submit(m_ShaderLibrary->Get("Basic3D"), m_VertexArray, model);
        Airwave::Renderer::EndScene();
    }

    void OnEvent(Airwave::Event &event) override
    {
        Airwave::EventDispatcher dispatcher(event);
        dispatcher.Dispatch<Airwave::KeyPressedEvent>(std::bind(&ExampleLayer::OnKeyPressedEvent, this, std::placeholders::_1));
        dispatcher.Dispatch<Airwave::MouseScrolledEvent>(std::bind(&ExampleLayer::OnMouseScrolledEvent, this, std::placeholders::_1));
    }

    bool OnKeyPressedEvent(Airwave::KeyPressedEvent &event)
    {

        return false;
    }

    bool OnMouseScrolledEvent(Airwave::MouseScrolledEvent &event)
    {
        return false;
    }

    void OnImGuiRender(float deltaTime) override
    {
        ImGui::Begin("Test");
        ImGui::Text("Hello World!");
        ImGui::End();
    }

private:
    std::shared_ptr<Airwave::Camera> m_Camera;

    std::shared_ptr<Airwave::ShaderLibrary> m_ShaderLibrary;

    std::shared_ptr<Airwave::VertexArray> m_VertexArray;

    float m_Rotation = 0.0f;
};

class Sandbox : public Airwave::Application
{
public:
    void OnConfiguration(Airwave::AppSettings *settings) override
    {
        settings->width = 1280;
        settings->height = 720;
        settings->title = "Normal Cube";
    }

    void OnInit() override
    {
        PushLayer(std::make_shared<ExampleLayer>());
    }
};

Airwave::Application *Airwave::CreateApplication()
{
    return new Sandbox();
}
