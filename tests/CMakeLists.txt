find_package(GTest QUIET)

if(NOT GTest_FOUND)
    include(FetchContent)
    FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
    )
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(googletest)
endif()

add_executable(pikuma_tests
    test_util.cpp
)

target_link_libraries(pikuma_tests
    PRIVATE
    GTest::gtest_main
    modules
)

target_include_directories(pikuma_tests PRIVATE ${CMAKE_SOURCE_DIR}/modules/include)

target_compile_features(pikuma_tests PRIVATE cxx_std_17)

include(GoogleTest)
gtest_discover_tests(pikuma_tests)
