cmake_minimum_required(VERSION 3.8)

add_library(Core 

    "Application/Application.cpp"
)

target_link_libraries(Core PRIVATE Platform)