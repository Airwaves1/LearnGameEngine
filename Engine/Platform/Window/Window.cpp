#include "Window/Window.h"
#include "Window/WindowsWindow.h"

namespace Airwave
{
    Window* Window::Create(const WindowProps& props)
    {
        return new WindowsWindow(props);
    }

}