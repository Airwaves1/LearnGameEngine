#include "AirwaveEngine.h"
#include "Camera/Camera.h"
#include "Camera/PerspectiveCamera.h"

#include "ECS/Component/TransformComponent.h"
#include "Geometry/GeometryUtils.h"
#include "Renderer/RenderCommand.h"

#include <memory>

#include "Utils/Log.h"
#include "imgui.h"

#include "ECS/Component/ComponentSerializer.h"

class ExampleLayer : public Airwave::Layer
{
public:
    ExampleLayer()
        : Layer("Example")
    {
        Airwave::ComponentSerializer::RegisterComponentTypes();

        // 创建组件
        Airwave::TransformComponent transform;
        transform.position = {1.0f, 2.0f, 3.0f};
        transform.rotation = {0.0f, 0.0f, 0.0f};
        transform.scale = {1.0f, 1.0f, 1.0f};

        // 序列化组件
        auto j = Airwave::ComponentSerializer::Serialize(transform);

        // 指定保存目录和文件名
        const std::string directory = ASSETS_JSON_DIR;
        const std::string filename = "TransformComponent.json";
        const std::string filepath = directory + filename;

        // 确保目录存在
        if (!std::filesystem::exists(directory))
        {
            if (std::filesystem::create_directories(directory))
            {
                std::cout << "Created directory: " << directory << std::endl;
            }
            else
            {
                std::cerr << "Failed to create directory: " << directory << std::endl;
            }
        }

        // 保存到文件
        std::ofstream outFile(filepath);
        if (outFile.is_open())
        {
            outFile << j.dump(4); // Pretty print with an indent of 4 spaces
            outFile.close();
            std::cout << "Saved to file: " << filepath << std::endl;
        }
        else
        {
            std::cerr << "Failed to open file for writing.\n";
        }
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
        m_ShaderLibrary->Load("Screen", ASSETS_SHADER_DIR "00/Screen.vert", ASSETS_SHADER_DIR "00/Screen.frag");

        // 构建纹理
        m_Texture_0 = Airwave::Texture2D::Create(ASSETS_TEXTURE_DIR "R-C.jpeg");
        m_Texture_1 = Airwave::Texture2D::Create(ASSETS_TEXTURE_DIR "container2.png");

        auto shader = m_ShaderLibrary->Get("TextureCube");
        shader->Bind();
        shader->UploadUniformInt("u_Texture_0", 0);
        shader->UploadUniformInt("u_Texture_1", 1);

        auto screenShader = m_ShaderLibrary->Get("Screen");
        screenShader->Bind();
        screenShader->UploadUniformInt("u_ScreenTexture", 0);

        // 立方体
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

        m_Framebuffer = Airwave::Framebuffer::Create(app.GetWindow().GetWidth(), app.GetWindow().GetHeight(), {1, 1, 0, true});
    }

    void OnDetach() override
    {
    }

    void OnUpdate(float deltaTime) override
    {
        OnFrameBufferResize(app.GetWindow().GetWidth(), app.GetWindow().GetHeight());

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
        Airwave::Renderer::BeginScene(m_Camera);
        {
            m_Framebuffer->Bind();

            Airwave::RenderCommand::Clear();
            Airwave::RenderCommand::Enable(Airwave::RenderState::DepthTest);

            m_Texture_0->Bind(0);
            m_Texture_1->Bind(1);
            Airwave::Renderer::Submit(m_ShaderLibrary->Get("TextureCube"), m_VertexArray, m_Modle);

            m_Framebuffer->Unbind();
            Airwave::RenderCommand::Clear();

            // 将解析后的Framebuffer纹理绘制到屏幕上
            m_Framebuffer->RenderToFullScreenQuad(m_ShaderLibrary->Get("Screen"));
        }
        Airwave::Renderer::EndScene();
    }

    void OnImGuiRender(float deltaTime) override
    {
        static int flag = 0.0f;
        flag++;
        if (flag % 36 == 0)
        {
            m_FPS = 1.0f / deltaTime;
        }

        ImGui::Begin("Settings");
        ImGui::Text("FPS: %.2f", m_FPS);
        ImGui::End();
    }

    void OnFrameBufferResize(int width, int height)
    {
        m_Framebuffer->Resize(width, height);
    }

private:
    std::shared_ptr<Airwave::Camera> m_Camera;

    std::shared_ptr<Airwave::ShaderLibrary> m_ShaderLibrary;

    std::shared_ptr<Airwave::Texture2D> m_Texture_0;
    std::shared_ptr<Airwave::Texture2D> m_Texture_1;

    std::shared_ptr<Airwave::VertexArray> m_VertexArray;

    std::shared_ptr<Airwave::Framebuffer> m_Framebuffer;

    float m_Rotation = 0.0f;
    glm::mat4 m_Modle;

    float m_FPS = 0.0f;
};

class SandboxApp : public Airwave::Application
{
public:
    void OnConfiguration(Airwave::AppSettings *settings) override
    {
        settings->width = 1280;
        settings->height = 720;
        settings->title = "PackFBO";
    }

    void OnInit() override
    {
        PushLayer(std::make_shared<ExampleLayer>());
    }
};

Airwave::Application *Airwave::CreateApplication()
{
    return new SandboxApp();
}
