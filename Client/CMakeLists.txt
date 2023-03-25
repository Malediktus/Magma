project(Client VERSION 0.0.1 DESCRIPTION "The Test Playground for Magma")

file (GLOB_RECURSE GLSL_SOURCE_FILES
    "assets/OpenGL/*.frag"
    "assets/OpenGL/*.vert"
)

file (GLOB_RECURSE CPP_SOURCE_FILES
    "src/*.cpp"
    "src/*.h"
)

add_executable(${PROJECT_NAME}
    ${CPP_SOURCE_FILES}
    ${GLSL_SOURCE_FILES}
)

source_group("Shaders/OpenGL" FILES ${GLSL_SOURCE_FILES})

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)
target_link_libraries(${PROJECT_NAME} Magma)

if (MSVC)
add_custom_command(TARGET ${PROJECT_NAME} PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/assets/ ${EXECUTABLE_OUTPUT_PATH}/${CMAKE_BUILD_TYPE}/assets/)
else ()
add_custom_command(TARGET ${PROJECT_NAME} PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/assets/ ${EXECUTABLE_OUTPUT_PATH}/assets/)
endif()
