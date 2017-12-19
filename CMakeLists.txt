cmake_minimum_required(VERSION 3.7)
project(cgproject)
set(CMAKE_CXX_STANDARD 11)

include_directories(lib)

if (APPLE)
    message("runing on mac environment")
    set(INC_DIR /usr/local/include)
    set(LINK_DIR /usr/local/lib)
    include_directories(${INC_DIR})
    link_directories(${LINK_DIR})
ELSEIF (UNIX)
    message("running on unix environment")
    find_package(glfw3 REQUIRED)
endif ()


set(GLAD lib/glad/glad.h lib/glad.c)

set(SOURCE_FILES main.cpp ${GLAD})

add_executable(demo ${SOURCE_FILES})

target_link_libraries(demo glfw)