#include <AirwaveEngine.h>
#include <imgui.h>
// #include "Camera/OrthographicCamera.h"
#include "Camera/PerspectiveCamera.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "ECS/UUID.h"
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

        auto uuid = Airwave::UUID::Generate();
        LOG_INFO("UUID: {0}", uuid.ToString());

        m_Camera = std::make_shared<Airwave::PerspectiveCamera>(glm::radians(65.0f), width / height, 0.1f, 10000.0f);
        m_Camera->SetPosition({0.0f, 0.0f, 15.0f});

        m_ShaderLibrary = std::make_shared<Airwave::ShaderLibrary>();
        m_ShaderLibrary->Load("Texture", ASSETS_SHADER_DIR "00/Texture.vert", ASSETS_SHADER_DIR "00/Texture.frag");
        auto shader = m_ShaderLibrary->Load("Basic3D", ASSETS_SHADER_DIR "00/Basic3D.vert", ASSETS_SHADER_DIR "00/Basic3D.frag");

        glm::vec3 uniformColor = {0.8f, 0.3f, 0.6f};

        float vertexData[] = {
            // Positions         // UVs     // Normals
            // Front Face
            -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,
            0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
            0.5f, 0.5f, 0.5f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
            -0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,

            // Back Face
            -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f,
            0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, -1.0f,
            0.5f, 0.5f, -0.5f, 1.0f, 1.0f, 0.0f, 0.0f, -1.0f,
            -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, -1.0f,

            // Top Face
            -0.5f, 0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f,
            0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
            0.5f, 0.5f, 0.5f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f,
            -0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,

            // Bottom Face
            -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f,
            0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, -1.0f, 0.0f,
            0.5f, -0.5f, 0.5f, 1.0f, 1.0f, 0.0f, -1.0f, 0.0f,
            -0.5f, -0.5f, 0.5f, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f,

            // Left Face
            -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,
            -0.5f, -0.5f, 0.5f, 1.0f, 0.0f, -1.0f, 0.0f, 0.0f,
            -0.5f, 0.5f, 0.5f, 1.0f, 1.0f, -1.0f, 0.0f, 0.0f,
            -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f,

            // Right Face
            0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
            0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f,
            0.5f, 0.5f, 0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
            0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f};

        uint32_t indexData[] = {
            // Front Face
            0, 1, 2, 2, 3, 0,
            // Back Face
            4, 5, 6, 6, 7, 4,
            // Top Face
            8, 9, 10, 10, 11, 8,
            // Bottom Face
            12, 13, 14, 14, 15, 12,
            // Left Face
            16, 17, 18, 18, 19, 16,
            // Right Face
            20, 21, 22, 22, 23, 20};

        shader->Bind();
        shader->UploadUniformFloat3("u_Color", uniformColor);

        // uint32_t vbo, ibo;
        // glBindVertexArray(m_vao);
        // glGenVertexArrays(1, &m_vao);


        // glGenBuffers(1, &vbo);
        // glBindBuffer(GL_ARRAY_BUFFER, vbo);
        // glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);

        // glGenBuffers(1, &ibo);
        // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
        // glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indexData), indexData, GL_STATIC_DRAW);

        // // Position
        // glEnableVertexAttribArray(0);
        // glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)0);
        // // UV
        // glEnableVertexAttribArray(1);
        // glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(3 * sizeof(float)));
        // // Normal
        // glEnableVertexAttribArray(2);
        // glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(5 * sizeof(float)));

        // glBindVertexArray(0);

        m_VertexArray = Airwave::VertexArray::Create();

        auto vertexBuffer = Airwave::VertexBuffer::Create(vertexData, sizeof(vertexData));
        auto bufferLayout = Airwave::BufferLayout{
            {Airwave::ShaderDataType::FLOAT3, "a_Position"},
            {Airwave::ShaderDataType::FLOAT2, "a_TexCoord"},
            {Airwave::ShaderDataType::FLOAT3, "a_Normal"}};
        vertexBuffer->SetBufferLayout(bufferLayout);
        m_VertexArray->AddVertexBuffer(vertexBuffer);

        auto indexBuffer = Airwave::IndexBuffer::Create(indexData, sizeof(indexData));
        m_VertexArray->SetIndexBuffer(indexBuffer);

        m_VertexArray->Unbind();
    }

    void OnUpdate(float deltaTime) override
    {
        glViewport(0, 0, Airwave::Application::Get().GetWindow().GetWidth(), Airwave::Application::Get().GetWindow().GetHeight());
        Airwave::RenderCommand::SetClearColor({0.2, 0.2, 0.2, 1.0});
        Airwave::RenderCommand::Clear();

        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, 0.0f, -10.0f));
        model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));
        model = glm::rotate(model, glm::radians(m_Rotation), glm::vec3(1.0f, 1.0f, 1.0f));
        m_Rotation += 5.0f * deltaTime;


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

    uint32_t m_vao;
    float m_Rotation = 0.0f;
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
