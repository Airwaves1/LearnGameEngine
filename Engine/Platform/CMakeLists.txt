cmake_minimum_required(VERSION 3.8)

add_library(Platform 

    "Utils/Log.cpp"
    "Utils/FileUtils.cpp"

    "Window/Window.cpp"
    "Window/Windows/WindowsWindow.cpp"
    "Window/Windows/WindowsInput.cpp"

    "Graphics/OpenGL/OpenGLContext.cpp"
    "Graphics/OpenGL/OpenGLRendererAPI.cpp"
    "Graphics/OpenGL/OpenGLFrameBuffer.cpp"
    "Graphics/OpenGL/OpenGLVertexArray.cpp"
    "Graphics/OpenGL/OpenGLBuffer.cpp"
    "Graphics/OpenGL/OpenGLShader.cpp"
    "Graphics/OpenGL/OpenGLTexture.cpp"

)


target_link_libraries(Platform PRIVATE ThirdParty)