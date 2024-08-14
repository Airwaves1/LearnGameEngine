cmake_minimum_required (VERSION 3.8)

project(FrameBuffer)


add_executable(FrameBuffer 
    "FrameBuffer.cpp"
)

target_link_libraries(FrameBuffer PRIVATE Engine)
