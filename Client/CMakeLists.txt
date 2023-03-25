project(Client VERSION 0.0.1 DESCRIPTION "The Test Playground for Magma")

file (GLOB_RECURSE GLSL_SPIRV_SOURCE_FILES
    "assets/Vulkan/*.frag"
    "assets/Vulkan/*.vert"
)

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

source_group("Shaders/Vulkan" FILES ${GLSL_SPIRV_SOURCE_FILES})
source_group("Shaders/OpenGL" FILES ${GLSL_SOURCE_FILES})

if (APPLE)
set(GLSL_COMPILER "$ENV{HOME}/VulkanSDK/1.3.239.0/macOS/bin/glslc") # FIXME: Hardcoded

foreach(GLSL ${GLSL_SPIRV_SOURCE_FILES})
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
else()
message(STATUS "Please compile shaders manually, automic shader compilation is only supported on macos currently")
endif()

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)
target_link_libraries(${PROJECT_NAME} Magma)

if (MSVC)
add_custom_command(TARGET ${PROJECT_NAME} PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/assets/ ${EXECUTABLE_OUTPUT_PATH}/${CMAKE_BUILD_TYPE}/assets/)
else ()
add_custom_command(TARGET ${PROJECT_NAME} PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/assets/ ${EXECUTABLE_OUTPUT_PATH}/assets/)
endif()
