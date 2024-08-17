cmake_minimum_required(VERSION 3.8)

add_library(Core 

    "Base/Layer.cpp"
    "Base/LayerStack.cpp"

    "Application/Application.cpp"

    "Renderer/RendererAPI.cpp"
    "Renderer/Renderer.cpp"
    "Renderer/RenderCommand.cpp"

    "Renderer/Buffers/FrameBuffer.cpp"
    "Renderer/Buffers/VertexArray.cpp"
    "Renderer/Buffers/Buffer.cpp"
    
    "Renderer/Shaders/Shader.cpp"
    "Renderer/Shaders/ShaderLibrary.cpp"
    
    "Renderer/Textures/Texture.cpp"
    "Renderer/Textures/Texture2D.cpp"

    "Geometry/GeometryUtils.cpp"
    
    "ImGui/ImGuiLayer.cpp"

    "Camera/Camera.cpp"
    "Camera/OrthographicCamera.cpp"
    "Camera/PerspectiveCamera.cpp"


    "ECS/UUID.cpp"
    "ECS/Node.cpp"
    "ECS/Scene.cpp"
    "ECS/Entity.cpp"

)

target_link_libraries(Core PRIVATE Platform)