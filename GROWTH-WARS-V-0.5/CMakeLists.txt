cmake_minimum_required(VERSION 3.24)

project(cpp_practice LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

set(RAYLIB_VERSION 6.0)

FetchContent_Declare(
    raylib
    GIT_REPOSITORY https://github.com/raysan5/raylib.git
    GIT_TAG ${RAYLIB_VERSION}
    GIT_SHALLOW TRUE
)

FetchContent_MakeAvailable(raylib)

add_executable(cpp_practice growth_wars.cpp)

target_link_libraries(cpp_practice PRIVATE raylib)