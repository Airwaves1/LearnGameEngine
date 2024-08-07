cmake_minimum_required (VERSION 3.8)


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(Sandbox)

set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -Os -Wall")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Os -Wall")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/build/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/build/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/build/bin)


#资源文件配置
add_definitions(-DRES_ROOT_DIR="${CMAKE_CURRENT_SOURCE_DIR}/Engine/Resource/")
set(RES_ROOT_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Engine/Resource/")


if(WIN32)
    message("++ Platform: Windows")
    add_definitions(-DAW_PLATFORM_WINDOWS)
elseif(APPLE)
    message("++ Platform: MacOS")
    add_definitions(-DAW_PLATFORM_MACOS)
elseif(UNIX)
    message("++ Platform: Linux")
    add_definitions(-DAW_PLATFORM_LINUX)
else()
    message("++ Platform: Unsupported")
endif()


#debug
add_definitions(-DAW_ENABLE_ASSERTS)

#添加头文件目录
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/Engine)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/Engine/Core)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/Engine/Platform)

#添加第三方库头文件
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/Engine/ThirdParty)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/Engine/ThirdParty/glfw/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/Engine/ThirdParty/glad/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/Engine/ThirdParty/imgui)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/Engine/ThirdParty/imgui/backends)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/Engine/ThirdParty/glm)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/Engine/ThirdParty/stb_image)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/Engine/ThirdParty/entt/single_include)

#添加子目录
add_subdirectory(Engine)
add_subdirectory(Sandbox)

