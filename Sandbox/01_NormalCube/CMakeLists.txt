cmake_minimum_required (VERSION 3.8)

project(01_NormalCube)


add_executable(01_NormalCube 
    "NormalCube.cpp"
)

target_link_libraries(01_NormalCube PRIVATE Engine)
