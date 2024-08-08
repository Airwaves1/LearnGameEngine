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
        auto uuid = Airwave::UUID::Generate();
        LOG_INFO("UUID: {0}", uuid.ToString());

        m_Camera = std::make_unique<Airwave::PerspectiveCamera>(glm::radians(45.0f), 1.0f, 0.1f, 10000.0f);

        m_ShaderLibrary = std::make_shared<Airwave::ShaderLibrary>();
        m_ShaderLibrary->Load("Texture", ASSETS_SHADER_DIR "00/Texture.vert", ASSETS_SHADER_DIR "00/Texture.frag");
        auto shader = m_ShaderLibrary->Load("Basic3D", ASSETS_SHADER_DIR "00/Basic3D.vert", ASSETS_SHADER_DIR "00/Basic3D.frag");

        glm::vec3 uniformColor = {0.8f, 0.3f, 0.6f};
        // std::vector<Airwave::AWVertex> vertices;
        // std::vector<uint32_t> indices;
        // Airwave::GeometryUtils::CreateCube(vertices, indices);
        // size_t size;
        // std::vector<float> vertexData = Airwave::GeometryUtils::ConvertAWVertexToFloatArray(vertices);

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

        m_VertexArray.reset(Airwave::VertexArray::Create());
        m_VertexArray->Bind();

        // vertex buffer
        std::shared_ptr<Airwave::VertexBuffer> vb;
        vb.reset(Airwave::VertexBuffer::Create(vertexData, 192 * sizeof(float)));
        Airwave::BufferLayout layout = {
            {Airwave::ShaderDataType::FLOAT3, "a_Position"},
            {Airwave::ShaderDataType::FLOAT2, "a_TexCoord"},
            {Airwave::ShaderDataType::FLOAT3, "a_Normal"}};
        vb->SetBufferLayout(layout);
        // index buffer
        std::shared_ptr<Airwave::IndexBuffer> ib;
        ib.reset(Airwave::IndexBuffer::Create(indexData, 36));

        m_VertexArray->AddVertexBuffer(vb);
        m_VertexArray->SetIndexBuffer(ib);

        m_VertexArray->Unbind();
    }

    void OnUpdate(float deltaTime) override
    {
        glViewport(0, 0, Airwave::Application::Get().GetWindow().GetWidth(), Airwave::Application::Get().GetWindow().GetHeight());
        Airwave::RenderCommand::SetClearColor({0.5, 0.4, 0.7, 1.0});
        Airwave::RenderCommand::Clear();

        // 旋转30度
        glm::mat4 translation = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -5.0f));
        translation = glm::rotate(translation, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        // // 缩小0.5倍
        translation = glm::scale(translation, glm::vec3(0.1f, 0.1f, 0.1f));

        Airwave::Renderer::BeginScene(m_Camera.get());
        Airwave::Renderer::Submit(m_ShaderLibrary->Get("Basic3D"), m_VertexArray, translation);
        Airwave::Renderer::EndScene();

        Airwave::RenderCommand::DrwaIndexed(m_VertexArray);
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
    std::unique_ptr<Airwave::Camera> m_Camera;

    std::shared_ptr<Airwave::ShaderLibrary> m_ShaderLibrary;

    std::shared_ptr<Airwave::VertexArray> m_VertexArray;
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
