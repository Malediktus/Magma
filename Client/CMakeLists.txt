project(Client VERSION 0.0.1 DESCRIPTION "The Test Playground for Magma")

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -fdeclspec -fPIC")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -fdeclspec -fPIC")

file (GLOB_RECURSE GLSL_SOURCE_FILES
    "assets/*.frag"
    "assets/*.vert"
)

file (GLOB_RECURSE CPP_SOURCE_FILES
    "src/*.cpp"
    "src/*.h"
)

add_executable(${PROJECT_NAME}
    ${CPP_SOURCE_FILES}
    ${GLSL_SOURCE_FILES}
)

if (APPLE)
    set(GLSL_COMPILER "$ENV{HOME}/VulkanSDK/1.3.239.0/macOS/bin/glslc") # FIXME: Hardcoded
endif()

foreach(GLSL ${GLSL_SOURCE_FILES})
    set(SPIRV "${GLSL}.spv")
    add_custom_command(
        OUTPUT ${SPIRV}
        COMMAND ${GLSL_COMPILER} ${GLSL} -o ${SPIRV}
        DEPENDS ${GLSL}
    )
    list(APPEND SPIRV_BINARY_FILES ${SPIRV})
endforeach(GLSL)

add_custom_target(
    Shaders 
    DEPENDS ${SPIRV_BINARY_FILES}
)

add_dependencies(${PROJECT_NAME} Shaders)

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)
target_link_libraries(${PROJECT_NAME} Magma)

add_custom_command(TARGET ${PROJECT_NAME} PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/assets/ ${EXECUTABLE_OUTPUT_PATH}/assets/)