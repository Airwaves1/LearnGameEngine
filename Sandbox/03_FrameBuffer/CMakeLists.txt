cmake_minimum_required (VERSION 3.8)

project(03_FrameBuffer)


add_executable(03_FrameBuffer 
    "FrameBuffer.cpp"
)

target_link_libraries(03_FrameBuffer PRIVATE Engine)
