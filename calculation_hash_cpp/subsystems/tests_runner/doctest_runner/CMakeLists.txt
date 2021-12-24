set (DOCTEST_RUNNER_DIR ${CMAKE_CURRENT_SOURCE_DIR}/source)

file (
    GLOB
    SOURCE_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/source/*.cc
    HEADER_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/source/*.h)

add_library (doctest_runner ${SOURCE_FILES} ${HEADER_FILES})
target_link_libraries (doctest_runner PUBLIC doctest)
target_include_directories (doctest_runner PUBLIC ${DOCTEST_RUNNER_DIR})
