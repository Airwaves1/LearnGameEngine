#include <AirwaveEngine.h>

class ExampleLayer : public Airwave::Layer
{
public:
    ExampleLayer()
        : Layer("Example")
    {
    }

    void OnUpdate() override
    {
        // LOG_INFO("ExampleLayer::Update");
    }

    void OnEvent(Airwave::Event& event) override
    {
        // LOG_TRACE("{0}", event.ToString());
    }
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

Airwave::Application* Airwave::CreateApplication()
{
    return new Sandbox();
}