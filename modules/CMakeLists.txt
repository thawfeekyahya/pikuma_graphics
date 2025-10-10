file(GLOB SRCS "src/*.cpp")                                                                                              
set(HDR_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)

set(TARGET_NAME modules)

add_library(${TARGET_NAME} ${SRCS})

target_include_directories(${TARGET_NAME} PUBLIC  ${HDR_DIR})


file(GLOB HDRS CONFIGURE_DEPENDS "${HDR_DIR}/*.h")

source_group(TREE ${HDR_DIR} PREFIX "Headers" FILES ${HDRS})

target_link_libraries(${TARGET_NAME}
    PUBLIC
    SDL2
)
