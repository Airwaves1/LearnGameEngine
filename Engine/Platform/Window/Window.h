#ifndef WINDOW_H
#define WINDOW_H

#include "Utils/Common.h"
#include "Event/Event.h"

namespace Airwave
{


    class Window
    {
    public:
        using EventCallbackFn = std::function<void(Event &)>;

        virtual ~Window() {}

        virtual void OnUpdate() = 0;

        virtual uint32_t GetWidth() const = 0;
        virtual uint32_t GetHeight() const = 0;

        // Window attributes
        virtual void SetEventCallback(const EventCallbackFn &callback) = 0;
        virtual void SetVSync(bool enabled) = 0;
        virtual bool IsVSync() const = 0;

        virtual void *GetNativeWindow() const = 0;

        static Window *Create(uint32_t width = 1280, uint32_t height = 720, const std::string &title = "Airwave Engine");
    };

} // namespace Airwave

#endif // WINDOW_H