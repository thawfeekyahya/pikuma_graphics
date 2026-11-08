# Shared rendering code: vectors, meshes, color buffer, drawing, SDL window.
add_library(pikuma_core
    src/color_buffer.cpp
    src/draw.cpp
    src/mesh.cpp
    src/sdl_window.cpp
    src/vector.cpp
)

target_include_directories(pikuma_core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(pikuma_core PUBLIC SDL2::SDL2)
target_compile_options(pikuma_core PRIVATE ${PIKUMA_WARNINGS})
