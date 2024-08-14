cmake_minimum_required (VERSION 3.8)

project(NormalCube)


add_executable(NormalCube 
    "NormalCube.cpp"
)

target_link_libraries(NormalCube PRIVATE Engine)
