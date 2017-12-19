cmake_minimum_required(VERSION 3.7)
project(untitled)

set(CMAKE_CXX_STANDARD 11)
set(INC_DIR /usr/local/include)
set(LINK_DIR /usr/local/lib)
set(SOURCE_FILES main.cpp glad.c)
include_directories(${INC_DIR})
link_directories(${LINK_DIR})

add_executable(untitled ${SOURCE_FILES})
target_link_libraries(untitled glfw)