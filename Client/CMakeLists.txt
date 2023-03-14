project(Sandbox VERSION 0.0.1 DESCRIPTION "The Test Playground for Magma")

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -fdeclspec -fPIC")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -fdeclspec -fPIC")

add_executable(${PROJECT_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/src/ClientApp.cpp)

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)
target_link_libraries(${PROJECT_NAME} Magma)

file(COPY assets DESTINATION ${CMAKE_BINARY_DIR}/${PROJECT_NAME})