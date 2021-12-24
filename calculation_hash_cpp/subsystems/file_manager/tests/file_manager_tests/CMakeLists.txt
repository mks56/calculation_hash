file (GLOB SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/source/*.cc)

add_executable (file_manager_tests ${SOURCE_FILES})

target_link_libraries (
    file_manager_tests
    doctest
    doctest_runner
    file_manager
    reference_data)
