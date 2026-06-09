cmake_minimum_required(VERSION 3.22)

project(flux)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# helps with clangd lsp issues in neovim
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# find some libraries
find_package(OpenGL REQUIRED)
# opengl math
find_package(glm CONFIG REQUIRED)
# window and gives opengl context
find_package(glfw3 CONFIG REQUIRED)
# find_package(CUDAToolkit REQUIRED)

# imgui?? overlay on top of glfw for editing values such as number of particles
# glad? modern opengl function loader? used in modern systems
# so glfw creates window + opengl context
# glad loads all modern gl functions into context
# opengl can be used to render in context

# .hpp files are able to be imported via <> instead of ""
# for internal files
file(GLOB_RECURSE sources src/*.cpp)

# imgui sources to combine with executable
set(imgui_sources
      external/imgui/imgui.cpp
      external/imgui/imgui_draw.cpp
      external/imgui/imgui_tables.cpp
      external/imgui/imgui_widgets.cpp
      external/imgui/backends/imgui_impl_glfw.cpp
      external/imgui/backends/imgui_impl_opengl3.cpp)

add_executable(main main.cpp ${sources} ${imgui_sources})
target_include_directories(main PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
                                       ${CMAKE_CURRENT_SOURCE_DIR}/external
                                       ${CMAKE_CURRENT_SOURCE_DIR}/external/imgui
                                       ${CMAKE_CURRENT_SOURCE_DIR}/external/imgui/backends)

target_link_libraries(main OpenGL::GL
                           glm::glm
                           glfw)
