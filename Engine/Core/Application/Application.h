#ifndef APPLICATION_H
#define APPLICATION_H

#include "Utils/Common.h"
#include "Window/Window.h"
#include "Base/LayerStack.h"
#include "ImGui/ImGuiLayer.h"

#include "Renderer/VertexArray.h"
#include "Renderer/Buffer.h"
#include "Renderer/Shader.h"
namespace Airwave
{
    class Event;
    class WindowCloseEvent;

    class Application
    {
    public:
        Application();
        virtual ~Application();

        void Run();

        void OnEvent(Event &e);

        void PushLayer(std::shared_ptr<Layer> layer);
        std::shared_ptr<Layer> PopLayer();

        static Application &Get();

        Window &GetWindow() { return *m_Window; }

    private:
        bool OnWindowClose(WindowCloseEvent &e);

    private:
        static Application *s_Instance;

        std::unique_ptr<Window> m_Window;
        std::shared_ptr<ImGuiLayer> m_ImGuiLayer;

        bool b_Running = true;
        LayerStack m_LayerStack;


    private:
        std::unique_ptr<Shader> m_Shader;
        std::shared_ptr<VertexArray> m_VertexArray;
        
    };

    // To be defined in CLIENT
    Application *CreateApplication();

} // namespace  Airwave

#endif // APPLICATION_H