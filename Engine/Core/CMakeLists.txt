cmake_minimum_required(VERSION 3.8)

add_library(Core 

    "Base/Layer.cpp"
    "Base/LayerStack.cpp"

    "Application/Application.cpp"

    "Renderer/RendererAPI.cpp"
    "Renderer/Renderer.cpp"
    "Renderer/RenderCommand.cpp"
    "Renderer/VertexArray.cpp"
    "Renderer/Buffer.cpp"
    "Renderer/Shader.cpp"
    "Renderer/ShaderLibrary.cpp"
    "Renderer/Texture.cpp"
    
    "ImGui/ImGuiLayer.cpp"

    "Camera/Camera.cpp"
    "Camera/OrthographicCamera.cpp"


)

target_link_libraries(Core PRIVATE Platform)