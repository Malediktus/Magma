add_subdirectory(vendor/spdlog)
add_subdirectory(vendor/glfw)
add_subdirectory(vendor/glm)

if (MAGMA_RENDERER_VULKAN)
    find_package(Vulkan REQUIRED)
endif()

project(Magma VERSION 0.0.1 DESCRIPTION "The Magma Game Engine Library")

file (GLOB_RECURSE CPP_SOURCE_FILES
    "src/Magma/*.cpp"
    "src/Magma/*.h"
)

add_library(${PROJECT_NAME} STATIC
    ${CPP_SOURCE_FILES}
)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_definitions(${PROJECT_NAME} PRIVATE _DEBUG)
endif()

target_compile_definitions(${PROJECT_NAME} PRIVATE MG_EXPORT)
target_compile_definitions(${PROJECT_NAME} PRIVATE MG_ASSERT)
target_compile_definitions(${PROJECT_NAME} PRIVATE MG_ASSERTIONS_ENABLED)
target_precompile_headers(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src/Magma/pch.h)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)
if (MAGMA_RENDERER_VULKAN)
    target_compile_definitions(${PROJECT_NAME} PRIVATE MG_VULKAN)
    target_link_libraries(${PROJECT_NAME} spdlog glfw ImGui Vulkan::Vulkan glm_shared)
else ()
    target_compile_definitions(${PROJECT_NAME} PRIVATE MG_OPENGL)
    target_link_libraries(${PROJECT_NAME} spdlog glfw ImGui glm_shared)
endif()

project(ImGui VERSION 0.0.1 DESCRIPTION "The Magma Engine ImGui Build")

if (MAGMA_RENDERER_VULKAN)
add_library(${PROJECT_NAME} STATIC
    ${CMAKE_CURRENT_SOURCE_DIR}/vendor/imgui/imconfig.h
    ${CMAKE_CURRENT_SOURCE_DIR}/vendor/imgui/imgui_draw.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/vendor/imgui/imgui_demo.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/vendor/imgui/imgui_internal.h
    ${CMAKE_CURRENT_SOURCE_DIR}/vendor/imgui/imgui_tables.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/vendor/imgui/imgui_widgets.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/vendor/imgui/imgui.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/vendor/imgui/imgui.h
    ${CMAKE_CURRENT_SOURCE_DIR}/vendor/imgui/imstb_rectpack.h
    ${CMAKE_CURRENT_SOURCE_DIR}/vendor/imgui/imstb_textedit.h
    ${CMAKE_CURRENT_SOURCE_DIR}/vendor/imgui/imstb_truetype.h
    
    ${CMAKE_CURRENT_SOURCE_DIR}/vendor/imgui/backends/imgui_impl_glfw.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/vendor/imgui/backends/imgui_impl_glfw.h
    ${CMAKE_CURRENT_SOURCE_DIR}/vendor/imgui/backends/imgui_impl_vulkan.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/vendor/imgui/backends/imgui_impl_vulkan.h
)
else ()
add_library(${PROJECT_NAME} STATIC
    ${CMAKE_CURRENT_SOURCE_DIR}/vendor/imgui/imconfig.h
    ${CMAKE_CURRENT_SOURCE_DIR}/vendor/imgui/imgui_draw.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/vendor/imgui/imgui_demo.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/vendor/imgui/imgui_internal.h
    ${CMAKE_CURRENT_SOURCE_DIR}/vendor/imgui/imgui_tables.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/vendor/imgui/imgui_widgets.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/vendor/imgui/imgui.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/vendor/imgui/imgui.h
    ${CMAKE_CURRENT_SOURCE_DIR}/vendor/imgui/imstb_rectpack.h
    ${CMAKE_CURRENT_SOURCE_DIR}/vendor/imgui/imstb_textedit.h
    ${CMAKE_CURRENT_SOURCE_DIR}/vendor/imgui/imstb_truetype.h
    
    ${CMAKE_CURRENT_SOURCE_DIR}/vendor/imgui/backends/imgui_impl_glfw.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/vendor/imgui/backends/imgui_impl_glfw.h
    ${CMAKE_CURRENT_SOURCE_DIR}/vendor/imgui/backends/imgui_impl_opengl3_loader.h
    ${CMAKE_CURRENT_SOURCE_DIR}/vendor/imgui/backends/imgui_impl_opengl3.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/vendor/imgui/backends/imgui_impl_opengl3.h
)
endif()

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/vendor/imgui)
if (MAGMA_RENDERER_VULKAN)
    target_link_libraries(${PROJECT_NAME} glfw Vulkan::Vulkan)
else ()
    target_link_libraries(${PROJECT_NAME} glfw)
endif()
