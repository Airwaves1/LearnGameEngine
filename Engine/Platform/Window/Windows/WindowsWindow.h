#ifndef WINDOWSWINDOW_H
#define WINDOWSWINDOW_H

#include "Window/Window.h"
#include "Renderer/GraphicsContext.h"

struct GLFWwindow;

namespace Airwave {

    class WindowsWindow : public Window
    {

    public:
        WindowsWindow(uint32_t width, uint32_t height, const std::string &title);
        virtual ~WindowsWindow();

        void OnUpdate() override;

        uint32_t GetWidth() const override { return m_Data.Width; }
        uint32_t GetHeight() const override { return m_Data.Height; }

        // Window attributes
        void SetEventCallback(const EventCallbackFn &callback) override { m_Data.EventCallback = callback; }
        void SetVSync(bool enabled) override;
        bool IsVSync() const override;

        inline void* GetNativeWindow() const override { return m_Window; }

    private:
        virtual void Init(uint32_t width, uint32_t height, const std::string &title);
        virtual void Shutdown();

    private:
        GLFWwindow *m_Window;

        GraphicsContext *m_Context;

        struct WindowData
        {
            std::string Title;
            uint32_t Width, Height;
            bool VSync;

            EventCallbackFn EventCallback;
        };

        WindowData m_Data;
    };


}



#endif // WINDOWSWINDOW_H