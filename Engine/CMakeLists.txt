cmake_minimum_required(VERSION 3.8)

project(AirwaveEngine)



add_library(Engine 
    "AirwaveEngine.cpp"
)
target_link_libraries(Engine PUBLIC Core)

# 添加子目录
add_subdirectory(Core)
add_subdirectory(Platform)
add_subdirectory(ThirdParty)