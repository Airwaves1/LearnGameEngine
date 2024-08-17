cmake_minimum_required (VERSION 3.8)

project(02_TextureCube)


add_executable(02_TextureCube 
    "TextureCube.cpp"
)

target_link_libraries(02_TextureCube PRIVATE Engine)
