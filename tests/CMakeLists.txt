find_package(GTest QUIET)

if(NOT GTest_FOUND)
    include(FetchContent)
    FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
        DOWNLOAD_EXTRACT_TIMESTAMP TRUE
    )
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(googletest)
endif()

add_executable(pikuma_tests
    test_vector.cpp
    test_mesh.cpp
    test_draw.cpp
    test_examples.cpp
)

target_link_libraries(pikuma_tests
    PRIVATE
    GTest::gtest_main
    examples
)

target_compile_definitions(pikuma_tests PRIVATE PIKUMA_ASSETS_DIR="${CMAKE_SOURCE_DIR}/assets")
target_compile_options(pikuma_tests PRIVATE ${PIKUMA_WARNINGS})

include(GoogleTest)
gtest_discover_tests(pikuma_tests)
