cmake_minimum_required (VERSION 3.8)

project(SandboxApp)


add_executable(SandboxApp 
    "Src/Sandbox.cpp"
)

target_link_libraries(SandboxApp PRIVATE Engine)

# 添加编译器选项以禁用未使用的头文件包含警告
target_compile_options(SandboxApp PRIVATE -Wno-unused-include)
