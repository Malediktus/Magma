add_subdirectory(vendor/easy_profiler)
add_subdirectory(vendor/googletest)
add_subdirectory(vendor/spdlog)
add_subdirectory(vendor/glfw)
add_subdirectory(vendor/glm)

find_package(Vulkan REQUIRED)

project(Magma VERSION 0.0.1 DESCRIPTION "The Magma Game Engine Library")

add_library(${PROJECT_NAME} STATIC
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Magma/pch.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Magma/Magma.h
    
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Magma/Core/Application.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Magma/Core/Application.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Magma/Core/Logger.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Magma/Core/Logger.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Magma/Core/Entry.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Magma/Core/Platform.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Magma/Core/Window.h

    ${CMAKE_CURRENT_SOURCE_DIR}/src/Magma/Event/Event.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Magma/Event/Event.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Magma/Event/KeyCode.h

    ${CMAKE_CURRENT_SOURCE_DIR}/src/Magma/Platform/Windows/Window.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Magma/Platform/Windows/Input.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Magma/Platform/MacOS/Window.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Magma/Platform/MacOS/Input.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Magma/Platform/Linux/Window.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Magma/Platform/Linux/Input.cpp

    ${CMAKE_CURRENT_SOURCE_DIR}/src/Magma/Renderer/Renderer.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Magma/Renderer/Renderer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Magma/Renderer/RenderingAPI.h

    ${CMAKE_CURRENT_SOURCE_DIR}/src/Magma/Platform/Vulkan/RenderingAPI.cpp
)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_definitions(${PROJECT_NAME} PRIVATE _DEBUG)
endif()

target_compile_definitions(${PROJECT_NAME} PRIVATE MG_EXPORT)
target_compile_definitions(${PROJECT_NAME} PRIVATE MG_ASSERT)
target_precompile_headers(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src/Magma/pch.h)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)
target_link_libraries(${PROJECT_NAME} easy_profiler spdlog glfw ImGui Vulkan::Vulkan glm_shared)

project(MagmaTest VERSION 0.0.1 DESCRIPTION "Tests for the Magma Game Engine Library")

add_executable(${PROJECT_NAME}
    ${CMAKE_CURRENT_SOURCE_DIR}/test/TestMain.cpp

    ${CMAKE_CURRENT_SOURCE_DIR}/src/Magma/pch.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Magma/Magma.h
    
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Magma/Core/Application.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Magma/Core/Application.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Magma/Core/Logger.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Magma/Core/Logger.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Magma/Core/Entry.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Magma/Core/Platform.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Magma/Core/Window.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Magma/Core/Input.h

    ${CMAKE_CURRENT_SOURCE_DIR}/src/Magma/Event/Event.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Magma/Event/Event.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Magma/Event/KeyCode.h

    ${CMAKE_CURRENT_SOURCE_DIR}/src/Magma/Platform/Windows/Window.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Magma/Platform/Windows/Input.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Magma/Platform/MacOS/Window.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Magma/Platform/MacOS/Input.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Magma/Platform/Linux/Window.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Magma/Platform/Linux/Input.cpp

    ${CMAKE_CURRENT_SOURCE_DIR}/src/Magma/Renderer/Renderer.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Magma/Renderer/Renderer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Magma/Renderer/RenderingAPI.h

    ${CMAKE_CURRENT_SOURCE_DIR}/src/Magma/Platform/Vulkan/RenderingAPI.cpp
)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_definitions(${PROJECT_NAME} PRIVATE _DEBUG)
endif()

target_compile_definitions(${PROJECT_NAME} PRIVATE MG_EXPORT)
target_compile_definitions(${PROJECT_NAME} PRIVATE MG_ASSERT)
target_precompile_headers(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src/Magma/pch.h)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)
target_link_libraries(${PROJECT_NAME} easy_profiler gtest spdlog glfw ImGui Vulkan::Vulkan glm_shared)

project(ImGui VERSION 0.0.1 DESCRIPTION "The Magma Engine ImGui Build")

add_library(${PROJECT_NAME} STATIC
    ${CMAKE_CURRENT_SOURCE_DIR}/vendor/imgui/imconfig.h
    ${CMAKE_CURRENT_SOURCE_DIR}/vendor/imgui/imgui_draw.cpp
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

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/vendor/imgui)
target_link_libraries(${PROJECT_NAME} glfw Vulkan::Vulkan)