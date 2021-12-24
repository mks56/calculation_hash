set (DOCTEST_DIR ${CMAKE_CURRENT_SOURCE_DIR}/source)

file (
    GLOB
    HEADER_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/source/*.h)

add_library(doctest ${HEADER_FILES})

target_include_directories(doctest PUBLIC ${DOCTEST_DIR})
