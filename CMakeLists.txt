cmake_minimum_required(VERSION 3.24)
include(FetchContent)

project(minigame)

set(CMAKE_CXX_STANDARD 17)

FetchContent_Declare(
        flecs
        GIT_REPOSITORY https://github.com/SanderMertens/flecs
        GIT_TAG v3.2.11
)
FetchContent_MakeAvailable(flecs)

FetchContent_Declare(
        raylib
        GIT_REPOSITORY https://github.com/raysan5/raylib
        GIT_TAG 5.0
)
FetchContent_MakeAvailable(raylib)

# Other Third Party Libraries
add_subdirectory(third_party/imgui) # From: https://github.com/ocornut/imgui

include_directories(src)
file(GLOB_RECURSE SRC_FILES src/*.cpp src/*.h)

# Add resources folder
file(GLOB_RECURSE RES_FILES res/*.png)
source_group("res" FILES ${RES_FILES})

foreach(FILE ${SRC_FILES} ${RES_FILES})
    get_filename_component(PARENT_DIR "${FILE}" DIRECTORY)
    file(RELATIVE_PATH PARENT_DIR_REL "${CMAKE_SOURCE_DIR}" "${PARENT_DIR}")
    string(REPLACE "/" "\\" GROUP_PATH "${PARENT_DIR_REL}")
    source_group("${GROUP_PATH}" FILES "${FILE}")
endforeach()

add_executable(minigame ${SRC_FILES} ${RES_FILES})

# Copy resources to build directory next to the executable
set(RESOURCE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/res")
file(COPY ${RES_FILES} DESTINATION ${RESOURCE_OUTPUT_DIRECTORY})

target_link_libraries(minigame flecs_static raylib imgui)