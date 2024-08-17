cmake_minimum_required(VERSION 3.8)

project(04_PackFBO)

add_executable(04_PackFBO
    "PackFBO.cpp"
)

target_link_libraries(04_PackFBO PRIVATE Engine)
