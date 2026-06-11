cmake_minimum_required(VERSION 3.22)

project(flux)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# helps with clangd lsp issues in neovim
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# find some libraries
# raylib
find_package(raylib QUIET)
# builds raylib if not found? must have required libraries to build
if (NOT raylib_FOUND)
    include(FetchContent)
    FetchContent_Declare(
        raylib
        GIT_REPOSITORY https://github.com/raysan5/raylib.git
        GIT_TAG 6.0
        GIT_SHALLOW 1
    )
    FetchContent_MakeAvailable(raylib)
endif()

# raylib-cpp
find_package(raylib_cpp QUIET)
if (NOT raylib_cpp_FOUND)
    if (NOT DEFINED RAYLIB_CPP_VERSION)
        set(RAYLIB_CPP_VERSION v6.0.0)
    endif()
    include(FetchContent)
    FetchContent_Declare(
        raylib_cpp
        GIT_REPOSITORY https://github.com/RobLoach/raylib-cpp.git
        GIT_TAG ${RAYLIB_CPP_VERSION}
    )
    FetchContent_MakeAvailable(raylib_cpp)
endif()

# .hpp files are able to be imported via <> instead of ""
# for internal files
file(GLOB_RECURSE sources src/*.cpp)

add_executable(main main.cpp ${sources})
target_include_directories(main PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
                                       ${CMAKE_CURRENT_SOURCE_DIR}/external)

target_link_libraries(main PUBLIC raylib raylib_cpp)
