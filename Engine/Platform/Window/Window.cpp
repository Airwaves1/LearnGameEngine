#include "Window/Window.h"
#include "Window/Windows/WindowsWindow.h"

namespace Airwave
{
    Window* Window::Create(const WindowProps& props)
    {
        return new WindowsWindow(props);
    }

}