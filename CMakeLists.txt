cmake_minimum_required(VERSION 3.20)

project(ANAENKIEngine)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#
# Math
#

add_library(Math

    src/math/geometrySystem.cpp
    src/math/matrix2D.cpp
    src/math/transform.cpp
)

target_include_directories(Math PUBLIC
    ${PROJECT_SOURCE_DIR}/src
)

#
# Core
#

add_library(Core

    src/core/logSystem.cpp
)

target_include_directories(Core PUBLIC
    ${PROJECT_SOURCE_DIR}/src
)

#
# Rendering
#

add_library(Rendering

    src/rendering/renderSystem.cpp
)

target_include_directories(Rendering PUBLIC
    ${PROJECT_SOURCE_DIR}/src
    $ENV{SDL_INCLUDE_PATH}
)

target_link_directories(Rendering PUBLIC
    $ENV{SDL_LIB_PATH}
)

target_link_libraries(Rendering PUBLIC
    Math

    SDL3
)

#
# Scene
#

add_library(Scene

    src/scene/testScene.cpp
)

target_include_directories(Scene PUBLIC
    ${PROJECT_SOURCE_DIR}/src
)

target_link_libraries(Scene PUBLIC
    Rendering
    Math
)

#
# Executable
#

add_executable(ANAENKIEngine
    src/main.cpp
)

target_include_directories(ANAENKIEngine PRIVATE
    ${PROJECT_SOURCE_DIR}/src
    $ENV{SDL_INCLUDE_PATH}
)

target_link_directories(ANAENKIEngine PRIVATE
    $ENV{SDL_LIB_PATH}
)

target_link_libraries(ANAENKIEngine PRIVATE

    Core
    Math
    Rendering
    Scene

    SDL3
    SDL3_ttf
)