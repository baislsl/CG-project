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
    link_libraries(${ASSIMP_LIBRARIES} ${OPENGL_LIBRARIES} glfw)
ELSEIF (UNIX)
    message("running on unix environment")
    find_package(OpenGL REQUIRED)
    find_package(glfw3 REQUIRED)
    find_package(Assimp REQUIRED)
    find_path(SIFTGPU_INCLUDE_DIR FreeImage.h)
    find_library(SIFTGPU_LIBRARY libfreeimage)
    include_directories(${SIFTGPU_INCLUDE_DIR})
    link_libraries(${ASSIMP_LIBRARIES} ${OPENGL_LIBRARIES} freeimage glfw )
ELSEIF (MINGW)
    message("running on MinGW environment")
    link_libraries(${OPENGL_LIBRARIES} glfw3 assimp freeimage)
endif ()

set(GLAD lib/glad/glad.h lib/glad/glad.c)
set(LINMATH lib/linmath.h)

set(SOURCE_FILES ${GLAD} ${LINMATH}
        src/main.cpp
        src/control/Camera.h
        src/control/Camera.cpp
        src/control/Cursor.h
        src/core/Input.h
        src/control/Cursor.cpp
        src/component/common/Component.h
        src/core/GameManager.cpp
        src/core/GameManager.h
        src/control/ResizeManager.cpp
        src/control/ResizeManager.h
        src/core/GameEntry.cpp
        src/core/GameEntry.h
        src/control/Shader.h
        src/control/Shader.cpp
        src/component/common/Mesh.h
        src/component/common/Mesh.cpp
        src/component/common/Model.h
        src/component/common/Model.cpp
        src/tool/stb_image.cpp
        src/tool/stb_image.h
        src/component/common/Object.cpp
        src/component/common/Object.h
        src/control/Light.h
        src/control/Light.cpp
        src/component/common/BaseShape.h
        src/component/Cube.h
        src/component/Cube.cpp
        src/component/Sphere.h
        src/component/Sphere.cpp
        src/component/Plane.h
        src/component/GrassFloor.cpp
        src/component/GrassFloor.h
        src/component/Plane.cpp
        src/component/GrassPlane.cpp
        src/component/GrassPlane.h
        src/control/TextureManager.cpp
        src/control/TextureManager.h
        src/component/TextureCube.cpp
        src/component/TextureCube.h
        src/game/WorldMap.cpp
        src/game/WorldMap.hpp
        src/component/Skybox.h
        src/component/Skybox.cpp
        src/control/KeyBoard.cpp
        src/control/KeyBoard.h
        src/component/drawable/Prism.hpp
        src/component/drawable/Prism.cpp
        src/component/drawable/TranslucenceCube.cpp
        src/component/drawable/TranslucenceCube.h
        src/component/TargetBox.cpp
        src/component/TargetBox.hpp
        src/json/JSONMapWriter.cpp
        src/json/JSONMapWriter.hpp
        src/json/JSONUtil.hpp src/component/drawable/Drawable.hpp src/component/drawable/WaterCube.hpp src/component/drawable/GrassCube.hpp src/component/drawable/TNTCube.hpp)
include_directories(src/control)
include_directories(src/core)
include_directories(src/component)
include_directories(src/tool)
include_directories(lib/glad)
include_directories(lib/KHR)
include_directories(src/component/common)
include_directories(src/game)
include_directories(src/json)
add_executable(demo ${SOURCE_FILES})
if (APPLE)
    target_link_libraries(demo "/usr/local/lib/libassimp.dylib")
    target_link_libraries(demo "/usr/local/lib/libfreeimageplus.3.17.0.dylib")
endif ()

add_executable(Test1 test/test.cpp)
