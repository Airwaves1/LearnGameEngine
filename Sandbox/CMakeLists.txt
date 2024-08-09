cmake_minimum_required (VERSION 3.8)

project(SandboxApp)


add_executable(SandboxApp 
    "Src/Sandbox.cpp"
)

target_link_libraries(SandboxApp PRIVATE Engine)
