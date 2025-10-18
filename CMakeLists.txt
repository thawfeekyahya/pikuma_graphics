cmake_minimum_required(VERSION 3.16)
project(pikuma VERSION 1.0 DESCRIPTION "Pikuma 3D from scratch" LANGUAGES C CXX)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_BUILD_TYPE DEBUG)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 17)

add_subdirectory(modules)
add_subdirectory(SDL)

add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME} 
    PRIVATE
    modules 
)
