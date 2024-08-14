#include "AirwaveEngine.h"
#include "Camera/Camera.h"
#include "Camera/PerspectiveCamera.h"

#include "Geometry/GeometryUtils.h"

class ExampleLayer : public Airwave::Layer
{
public:
    ExampleLayer()
        : Layer("Example")
    {
    }

    ~ExampleLayer()
    {
    }

    void OnAttach() override
    {
        // 初始化相机
        float aspect = (float)app.GetWindow().GetWidth() / (float)app.GetWindow().GetHeight();
        m_Camera = std::make_shared<Airwave::PerspectiveCamera>(glm::radians(65.0f), aspect, 0.1f, 10000.0f);

        // 构建着色器库
        m_ShaderLibrary = std::make_shared<Airwave::ShaderLibrary>();
        m_ShaderLibrary->Load("TextureCube", ASSETS_SHADER_DIR "00/Texture.vert", ASSETS_SHADER_DIR "00/Texture.frag");

        // 构建纹理
        m_Texture_0 = Airwave::Texture2D::Create(ASSETS_TEXTURE_DIR "awesomeface.png");
        m_Texture_1 = Airwave::Texture2D::Create(ASSETS_TEXTURE_DIR "R-C.jpeg");

        auto shader = m_ShaderLibrary->Get("TextureCube");
        shader->Bind();
        shader->UploadUniformInt("u_Texture_0", 0);
        shader->UploadUniformInt("u_Texture_1", 1);

        // 构建顶点数组
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

    void OnDetach() override
    {
    }

    void OnUpdate(float deltaTime) override
    {
        Airwave::RenderCommand::SetClearColor({0.5, 0.3, 0.8, 1.0});

        // 更新相机
        m_Camera->SetProjectionMatrix(glm::radians(65.0f), (float)app.GetWindow().GetWidth() / (float)app.GetWindow().GetHeight(), 0.1f, 10000.0f);

        m_Modle = glm::mat4(1.0f);
        m_Modle = glm::translate(m_Modle, glm::vec3(0.0f, 0.0f, -20.0f));
        m_Modle = glm::scale(m_Modle, glm::vec3(0.2f, 0.2f, 0.2f));
        m_Modle = glm::rotate(m_Modle, glm::radians(m_Rotation), glm::vec3(1.0f, 1.0f, 1.0f));
        m_Rotation += 15.0f * deltaTime;
    }

    void OnRender() override
    {
        Airwave::RenderCommand::Clear();

        Airwave::Renderer::BeginScene(m_Camera);
        {
            m_Texture_0->Bind(0);
            m_Texture_1->Bind(1);
            Airwave::Renderer::Submit(m_ShaderLibrary->Get("TextureCube"), m_VertexArray, m_Modle);
        }
        Airwave::Renderer::EndScene();
    }

    void OnImGuiRender(float deltaTime) override
    {
    }

private:
    std::shared_ptr<Airwave::Camera> m_Camera;

    std::shared_ptr<Airwave::ShaderLibrary> m_ShaderLibrary;

    std::shared_ptr<Airwave::Texture2D> m_Texture_0;
    std::shared_ptr<Airwave::Texture2D> m_Texture_1;

    std::shared_ptr<Airwave::VertexArray> m_VertexArray;

    float m_Rotation = 0.0f;
    glm::mat4 m_Modle;
};

class SandboxApp : public Airwave::Application
{

public:
    void OnConfiguration(Airwave::AppSettings *settings) override
    {
        settings->width = 1280;
        settings->height = 720;
        settings->title = "TextureCube";
    }

    void OnInit() override
    {
        m_LayerStack.PushLayer(std::make_shared<ExampleLayer>());
    }
    
};

Airwave::Application *Airwave::CreateApplication()
{
    return new SandboxApp();
}