cmake_minimum_required(VERSION 3.8)

project(AirwaveEngine)



add_library(Engine
    "AirwaveEngine.h"
    "AirwaveEngine.cpp"
)

target_link_libraries(Engine PUBLIC Core)


# 添加子目录
add_subdirectory(Core)
add_subdirectory(Platform)
add_subdirectory(ThirdParty)

# 添加编译器选项以禁用未使用的头文件包含警告
target_compile_options(Engine PRIVATE -Wno-unused-include)