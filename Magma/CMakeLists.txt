
add_subdirectory(vendor/easy_profiler)
add_subdirectory(vendor/googletest)
set(enable_cplusplus ON) # C++ support for garbage collector
add_subdirectory(vendor/bdwgc)

project(Magma VERSION 0.0.1 DESCRIPTION "The Magma Game Engine Library")

add_library(${PROJECT_NAME} STATIC
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Magma/pch.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Magma/Magma.h
    
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Magma/Core/Application.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Magma/Core/Application.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Magma/Core/Entry.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Magma/Core/Platform.h
)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_definitions(${PROJECT_NAME} PRIVATE _DEBUG)
endif()

target_compile_definitions(${PROJECT_NAME} PRIVATE MG_EXPORT)
target_compile_definitions(${PROJECT_NAME} PRIVATE MG_ASSERT)
target_precompile_headers(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src/Magma/pch.h)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)
target_link_libraries(${PROJECT_NAME} gc gccpp easy_profiler gtest)

project(MagmaTest VERSION 0.0.1 DESCRIPTION "Tests for the Magma Game Engine Library")

add_executable(${PROJECT_NAME}
    ${CMAKE_CURRENT_SOURCE_DIR}/test/TestMain.cpp

    ${CMAKE_CURRENT_SOURCE_DIR}/src/Magma/pch.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Magma/Magma.h
    
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Magma/Core/Application.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Magma/Core/Application.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Magma/Core/Entry.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Magma/Core/Platform.h
)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_definitions(${PROJECT_NAME} PRIVATE _DEBUG)
endif()

target_compile_definitions(${PROJECT_NAME} PRIVATE MG_EXPORT)
target_compile_definitions(${PROJECT_NAME} PRIVATE MG_ASSERT)
target_precompile_headers(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src/Magma/pch.h)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)
target_link_libraries(${PROJECT_NAME} gc gccpp easy_profiler gtest)

add_test(NAME ${PROJECT_NAME} COMMAND ${PROJECT_NAME})