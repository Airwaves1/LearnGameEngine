#ifndef APPLICATION_H
#define APPLICATION_H

#include "Utils/Common.h"
#include "Window/Window.h"
#include "Base/LayerStack.h"
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

        void OnEvent(Event& e);

        void PushLayer(std::shared_ptr<Layer> layer);
        std::shared_ptr<Layer> PopLayer();

    private:
        bool OnWindowClose(WindowCloseEvent& e);

        std::unique_ptr<Window> m_Window;

        bool b_Running = true;
        LayerStack m_LayerStack;
    };

    // To be defined in CLIENT
    Application* CreateApplication();

} // namespace  Airwave

#endif // APPLICATION_H