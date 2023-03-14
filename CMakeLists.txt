cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

project(MagmaEngine VERSION 0.0.1 DESCRIPTION "The Magma Game Engine")

add_subdirectory(Client)
add_subdirectory(Magma)