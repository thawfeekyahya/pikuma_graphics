# One library holding every course step. New exampleN.cpp files are picked up
# automatically (CONFIGURE_DEPENDS re-runs the glob on each build).
file(GLOB EXAMPLE_SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

add_library(examples ${EXAMPLE_SOURCES})
target_include_directories(examples PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(examples PUBLIC pikuma_core)
target_compile_options(examples PRIVATE ${PIKUMA_WARNINGS})
