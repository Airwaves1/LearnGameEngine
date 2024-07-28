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

#glm
add_subdirectory(glm)
option(GLM_ENABLE_CXX_17 "Enable C++ 17" ON)

#imgui
add_subdirectory(imgui)

#stb_image
add_subdirectory(stb_image)



target_link_libraries(ThirdParty PUBLIC glfw)
target_link_libraries(ThirdParty PUBLIC glad)
target_link_libraries(ThirdParty PUBLIC glm)
target_link_libraries(ThirdParty PUBLIC ImGui)
target_link_libraries(ThirdParty PUBLIC stb_image)