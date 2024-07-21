#include <AirwaveEngine.h>


#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <imgui.h>


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
        if(event.GetEventType() == Airwave::EventType::KeyPressed)
        {
            Airwave::KeyPressedEvent& e = (Airwave::KeyPressedEvent&)event;
            if(e.GetKeycode() == AW_KEY_TAB)
            {
                LOG_INFO("Tab key is pressed (event)!");
            }
        }
    }

    void OnImGuiRender() override
    {
        ImGui::Begin("Test");
        ImGui::Text("Hello World!");
        ImGui::End();
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