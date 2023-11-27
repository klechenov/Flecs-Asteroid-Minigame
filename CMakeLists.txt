cmake_minimum_required(VERSION 3.24)
include(FetchContent)

project(minigame)

set(CMAKE_CXX_STANDARD 17)

FetchContent_Declare(
        flecs
        GIT_REPOSITORY https://github.com/SanderMertens/flecs
        GIT_TAG v3.2.8
)
FetchContent_MakeAvailable(flecs)

FetchContent_Declare(
        raylib
        GIT_REPOSITORY https://github.com/raysan5/raylib
        GIT_TAG 4.5.0
)
FetchContent_MakeAvailable(raylib)

# Other Third Party Libraries
add_subdirectory(third_party/imgui) # From: https://github.com/ocornut/imgui

include_directories(src)
file(GLOB_RECURSE SRC_FILES src/*.cpp)
add_executable(minigame ${SRC_FILES})

target_link_libraries(minigame flecs_static raylib imgui)