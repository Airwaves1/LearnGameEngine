cmake_minimum_required(VERSION 3.8)

project(05_ECS_Camera)

add_executable(05_ECS_Camera
    "ECS_Camera.cpp"
)

target_link_libraries(05_ECS_Camera PRIVATE Engine)
