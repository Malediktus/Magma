cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(LIBRARY_OUTPUT_PATH "${CMAKE_BINARY_DIR}/bin")
set(EXECUTABLE_OUTPUT_PATH "${CMAKE_BINARY_DIR}/bin")

project(MagmaEngine VERSION 0.0.1 DESCRIPTION "The Magma Game Engine")

if (APPLE)
    set(MAGMA_RENDERER_VULKAN ON)
    message(STATUS "Renderer: Vulkan for MacOS")
else ()
    set(MAGMA_RENDERER_OPENGL ON)
    message(STATUS "Renderer: OpenGL 3")
endif()

add_subdirectory(Client)
add_subdirectory(Magma)