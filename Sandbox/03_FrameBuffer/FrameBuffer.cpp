#include "AirwaveEngine.h"
#include "Camera/Camera.h"
#include "Camera/PerspectiveCamera.h"

#include "Geometry/GeometryUtils.h"
#include "Renderer/RenderCommand.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

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
        m_ShaderLibrary->Load("Screen", ASSETS_SHADER_DIR "00/Screen.vert", ASSETS_SHADER_DIR "00/Screen.frag");

        // 构建纹理
        m_Texture_0 = Airwave::Texture2D::Create(ASSETS_TEXTURE_DIR "awesomeface.png");
        m_Texture_1 = Airwave::Texture2D::Create(ASSETS_TEXTURE_DIR "R-C.jpeg");

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

        // 屏幕四边形   
        std::vector<float> quadVertices = {
            -1.0f, 1.0f, 0.0f, 1.0f,
            -1.0f, -1.0f, 0.0f, 0.0f,
            1.0f, -1.0f, 1.0f, 0.0f,

            -1.0f, 1.0f, 0.0f, 1.0f,
            1.0f, -1.0f, 1.0f, 0.0f,
            1.0f, 1.0f, 1.0f, 1.0f};

        m_QuadVertexArray = Airwave::VertexArray::Create();
        {
            auto vertexBuffer = Airwave::VertexBuffer::Create(quadVertices.data(), quadVertices.size() * sizeof(float));
            auto bufferLayout = Airwave::BufferLayout{
                {Airwave::ShaderDataType::FLOAT2, "a_Position"},
                {Airwave::ShaderDataType::FLOAT2, "a_TexCoord"}};
            vertexBuffer->SetBufferLayout(bufferLayout);
            m_QuadVertexArray->AddVertexBuffer(vertexBuffer);
        }

        // 创建帧缓冲
        glGenFramebuffers(1, &m_FBO);
        glBindFramebuffer(GL_FRAMEBUFFER, m_FBO);

        // 创建颜色附件
        glGenTextures(1, &m_TextureColorbuffer);
        glBindTexture(GL_TEXTURE_2D, m_TextureColorbuffer);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, app.GetWindow().GetWidth(), app.GetWindow().GetHeight(), 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_TextureColorbuffer, 0);

        // 创建渲染缓冲对象
        glGenRenderbuffers(1, &m_RBO);
        glBindRenderbuffer(GL_RENDERBUFFER, m_RBO);
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, app.GetWindow().GetWidth(), app.GetWindow().GetHeight());
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_RBO);

        if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        {
            LOG_ERROR("Framebuffer is incomplete!");
        }

        glBindFramebuffer(GL_FRAMEBUFFER, 0);
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
            glBindFramebuffer(GL_FRAMEBUFFER, m_FBO);
            glEnable(GL_DEPTH_TEST);

            Airwave::RenderCommand::Clear();

            m_Texture_0->Bind(0);
            m_Texture_1->Bind(1);
            Airwave::Renderer::Submit(m_ShaderLibrary->Get("TextureCube"), m_VertexArray, m_Modle);

            glBindFramebuffer(GL_FRAMEBUFFER, 0);
            glDisable(GL_DEPTH_TEST);
            Airwave::RenderCommand::Clear();
            m_ShaderLibrary->Get("Screen")->Bind();
            m_QuadVertexArray->Bind();
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, m_TextureColorbuffer);
            glDrawArrays(GL_TRIANGLES, 0, 6);
        }
        Airwave::Renderer::EndScene();
    }

    void OnImGuiRender(float deltaTime) override
    {
    }

    void OnFrameBufferResize(int width, int height)
    {
        glBindFramebuffer(GL_FRAMEBUFFER, m_FBO);
        
        glBindTexture(GL_TEXTURE_2D, m_TextureColorbuffer);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);

        glBindRenderbuffer(GL_RENDERBUFFER, m_RBO);
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);

        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

private:
    std::shared_ptr<Airwave::Camera> m_Camera;

    std::shared_ptr<Airwave::ShaderLibrary> m_ShaderLibrary;

    std::shared_ptr<Airwave::Texture2D> m_Texture_0;
    std::shared_ptr<Airwave::Texture2D> m_Texture_1;

    std::shared_ptr<Airwave::VertexArray> m_VertexArray;

    std::shared_ptr<Airwave::VertexArray> m_QuadVertexArray;
    uint32_t m_FBO;
    uint32_t m_TextureColorbuffer;
    uint32_t m_RBO;

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
        settings->title = "FrameBuffer";
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