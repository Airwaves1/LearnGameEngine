cmake_minimum_required(VERSION 3.8)


add_library(ThirdParty Test.cpp)

#glfw
option(GLFW_BUILD_DOCS OFF)
option(GLFW_BUILD_EXAMPLES OFF)
option(GLFW_BUILD_TESTS OFF)
option(GLFW_INSTALL OFF)
add_subdirectory(glfw)

#glad
add_subdirectory(glad)


target_link_libraries(ThirdParty PUBLIC glfw)
target_link_libraries(ThirdParty PUBLIC glad)
