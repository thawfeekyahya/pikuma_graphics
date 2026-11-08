cmake_minimum_required(VERSION 3.16)
project(pikuma VERSION 1.0 DESCRIPTION "Pikuma 3D from scratch" LANGUAGES C CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Build type" FORCE)
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Warnings for our own code only (not SDL or GoogleTest).
if(MSVC)
    set(PIKUMA_WARNINGS /W4)
else()
    set(PIKUMA_WARNINGS -Wall -Wextra -Wpedantic)
endif()

include(CTest)

add_subdirectory(SDL)
add_subdirectory(modules)
add_subdirectory(examples)

add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE examples)
target_compile_options(${PROJECT_NAME} PRIVATE ${PIKUMA_WARNINGS})

add_custom_target(copy_assets
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/assets
    ${CMAKE_BINARY_DIR}/assets
)
add_dependencies(${PROJECT_NAME} copy_assets)

if(BUILD_TESTING)
    add_subdirectory(tests)
endif()
