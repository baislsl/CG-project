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

    find_package(OpenGL REQUIRED)
    find_package(GLUT REQUIRED)
    include_directories(${GLUT_INCLUDE_DIR} ${OPENGL_INCLUDE_DIR})
    link_libraries(${GLUT_LIBRARIES} ${OPENGL_LIBRARIES})
ELSEIF (UNIX)
    message("running on unix environment")
    find_package(OpenGL REQUIRED)
    find_package(glfw3 REQUIRED)
    find_package(Assimp REQUIRED)
endif ()

link_libraries(${ASSIMP_LIBRARIES} ${OPENGL_LIBRARIES} glfw)

set(GLAD lib/glad/glad.h lib/glad/glad.c)
set(LINMATH lib/linmath.h)

set(SOURCE_FILES ${GLAD} ${LINMATH}
        src/main.cpp
        src/control/Camera.h
        src/control/Cursor.h
        src/core/Input.h
        src/control/Cursor.cpp
        src/component/Component.h
        src/core/GameManager.cpp
        src/core/GameManager.h
        src/control/ResizeManager.cpp
        src/control/ResizeManager.h
        src/core/GameEntry.cpp
        src/core/GameEntry.h
        src/control/Shader.h
        src/component/Mesh.h
        src/component/Model.h
        src/tool/stb_image.cpp
        src/tool/stb_image.h
        src/component/Object.cpp
        src/component/Object.h
        src/control/Light.h
        src/component/BaseShape.h src/component/Cube.h src/component/Sphere.h src/component/Cylinder.h src/component/Plane.h)
include_directories(src/control)
include_directories(src/core)
include_directories(src/component)
include_directories(src/tool)
include_directories(lib/glad)
include_directories(lib/KHR)
add_executable(demo ${SOURCE_FILES})
if (APPLE)
    target_link_libraries(demo "/usr/local/lib/libassimp.dylib")
endif ()
