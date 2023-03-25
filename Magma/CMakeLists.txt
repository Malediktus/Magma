add_subdirectory(vendor/spdlog)
add_subdirectory(vendor/glfw)
add_subdirectory(vendor/glm)

find_package(Vulkan REQUIRED)
find_package(OpenGL REQUIRED)

project(Magma VERSION 0.0.1 DESCRIPTION "The Magma Game Engine Library")

file (GLOB_RECURSE CORE_SOURCE_FILES
    "src/Magma/Core/*.cpp"
    "src/Magma/Core/*.h"
)

file (GLOB_RECURSE EVENT_SOURCE_FILES
    "src/Magma/Event/*.cpp"
    "src/Magma/Event/*.h"
)

file (GLOB_RECURSE PLATFORM_LINUX_SOURCE_FILES
    "src/Magma/Platform/Linux/*.cpp"
    "src/Magma/Platform/Linux/*.h"
)

file (GLOB_RECURSE PLATFORM_WINDOWS_SOURCE_FILES
    "src/Magma/Platform/Windows/*.cpp"
    "src/Magma/Platform/Windows/*.h"
)

file (GLOB_RECURSE PLATFORM_MACOS_SOURCE_FILES
    "src/Magma/Platform/MacOS/*.cpp"
    "src/Magma/Platform/MacOS/*.h"
)

file (GLOB_RECURSE PLATFORM_OPENGL_SOURCE_FILES
    "src/Magma/Platform/OpenGL/*.cpp"
    "src/Magma/Platform/OpenGL/*.h"
)

file (GLOB_RECURSE RENDERER_SOURCE_FILES
    "src/Magma/Renderer/*.cpp"
    "src/Magma/Renderer/*.h"
)

file (GLOB_RECURSE SCENE_SOURCE_FILES
    "src/Magma/Scene/*.cpp"
    "src/Magma/Scene/*.h"
)

add_library(${PROJECT_NAME} STATIC
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Magma/pch.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Magma/Magma.h
    ${CORE_SOURCE_FILES}
    ${EVENT_SOURCE_FILES}
    ${PLATFORM_LINUX_SOURCE_FILES}
    ${PLATFORM_WINDOWS_SOURCE_FILES}
    ${PLATFORM_MACOS_SOURCE_FILES}
    ${PLATFORM_OPENGL_SOURCE_FILES}
    ${RENDERER_SOURCE_FILES}
    ${SCENE_SOURCE_FILES}
)

source_group("Interface" FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/Magma/pch.h ${CMAKE_CURRENT_SOURCE_DIR}/src/Magma/Magma.h)
source_group("Core" FILES ${CORE_SOURCE_FILES})
source_group("Event" FILES ${EVENT_SOURCE_FILES})
source_group("Platform/Linux" FILES ${PLATFORM_LINUX_SOURCE_FILES})
source_group("Platform/Windows" FILES ${PLATFORM_WINDOWS_SOURCE_FILES})
source_group("Platform/MacOS" FILES ${PLATFORM_MACOS_SOURCE_FILES})
source_group("Platform/OpenGL" FILES ${PLATFORM_OPENGL_SOURCE_FILES})
source_group("Renderer" FILES ${RENDERER_SOURCE_FILES})
source_group("Scene" FILES ${SCENE_SOURCE_FILES})

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_definitions(${PROJECT_NAME} PRIVATE _DEBUG)
endif()

target_compile_definitions(${PROJECT_NAME} PRIVATE MG_EXPORT)
target_compile_definitions(${PROJECT_NAME} PRIVATE MG_ASSERT)
target_compile_definitions(${PROJECT_NAME} PRIVATE MG_ASSERTIONS_ENABLED)
target_precompile_headers(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src/Magma/pch.h)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)
target_link_libraries(${PROJECT_NAME} spdlog::spdlog glfw ImGui stb_image glm::glm Glad)

project(Glad VERSION 0.0.1 DESCRIPTION "The Magma Engine Glad Build")
add_library(${PROJECT_NAME} STATIC ${CMAKE_CURRENT_SOURCE_DIR}/vendor/glad/src/glad.c)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/vendor/glad/include)

project(stb_image VERSION 0.0.1 DESCRIPTION "The Magma Engine stb_image Build")
add_library(${PROJECT_NAME} STATIC ${CMAKE_CURRENT_SOURCE_DIR}/vendor/stb_image/stb_image.h ${CMAKE_CURRENT_SOURCE_DIR}/vendor/stb_image/stb_image.cpp)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/vendor/stb_image)

project(ImGui VERSION 0.0.1 DESCRIPTION "The Magma Engine ImGui Build")
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

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/vendor/imgui)
target_link_libraries(${PROJECT_NAME} glfw)
