cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(LIBRARY_OUTPUT_PATH "${CMAKE_BINARY_DIR}/bin")
set(EXECUTABLE_OUTPUT_PATH "${CMAKE_BINARY_DIR}/bin")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++17")

project(MagmaEngine VERSION 0.0.1 DESCRIPTION "The Magma Game Engine")

add_subdirectory(Client)
add_subdirectory(Magma)