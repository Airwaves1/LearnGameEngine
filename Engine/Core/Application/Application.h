#ifndef APPLICATION_H
#define APPLICATION_H

#include "Utils/Common.h"
#include "Window/Window.h"
#include "Base/LayerStack.h"
#include "ImGui/ImGuiLayer.h"

#include <chrono>

namespace Airwave
{
    class Event;
    class WindowCloseEvent;
    class WindowResizeEvent;

    struct AppSettings
    {
        uint32_t width = 1280;
        uint32_t height = 720;
        std::string title = "Airwave Engine";
    };

    class Application
    {
    public:
        void Start(int argc, char *argv[]);
        void Stop();
        void MainLoop();

        void PushLayer(std::shared_ptr<Layer> layer);
        std::shared_ptr<Layer> PopLayer();

    public:
        static Application &Get();
        Window &GetWindow() { return *m_Window; }

        bool IsRunning() { return b_Running; }
        void Close() { b_Running = false; }
        void Pause() { b_Paused = true; }
        void Resume() { b_Paused ? b_Paused = false : b_Paused = true; }

    protected:
        virtual void OnConfiguration(AppSettings* settings) {}
        virtual void OnInit() {}
        virtual void OnDestory() {}

        virtual void OnEvent(Event &e);
        bool OnWindowClose(WindowCloseEvent &e);
        bool OnWindowResize(WindowResizeEvent &e);
        
        std::chrono::time_point<std::chrono::steady_clock> m_StartTimePoint;
        std::chrono::time_point<std::chrono::steady_clock> m_LastTimePoint;
        float m_DeltaTime = 0.0f;

        std::unique_ptr<Window> m_Window;
        std::shared_ptr<ImGuiLayer> m_ImGuiLayer;
        LayerStack m_LayerStack;

    private:
        void ParseArguments(int argc, char *argv[]);


    private:
        static Application *s_Instance;
        AppSettings m_AppSettings;

        bool b_Running = true;
        bool b_Paused = false;
    };

    // To be defined in CLIENT
    Application *CreateApplication();

} // namespace  Airwave

#endif // APPLICATION_H