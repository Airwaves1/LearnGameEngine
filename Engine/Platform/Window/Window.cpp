#include "Window/Window.h"
#include "Window/Windows/WindowsWindow.h"

namespace Airwave
{
    Window* Window::Create(uint32_t width, uint32_t height, const std::string& title)
    {
        return new WindowsWindow({width, height, title});
    }

}