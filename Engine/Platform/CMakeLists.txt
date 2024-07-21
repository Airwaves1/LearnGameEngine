cmake_minimum_required(VERSION 3.8)

add_library(Platform 

    "Utils/Log.cpp"

    "Window/Window.cpp"
    "Window/Windows/WindowsWindow.cpp"
    "Window/Windows/WindowsInput.cpp"

    "Graphics/OpenGL/OpenGLContext.cpp"

)


target_link_libraries(Platform PRIVATE ThirdParty)