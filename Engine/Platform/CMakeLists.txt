cmake_minimum_required(VERSION 3.8)

add_library(Platform 

    "Utils/Log.cpp"
)


target_link_libraries(Platform PRIVATE ThirdParty)