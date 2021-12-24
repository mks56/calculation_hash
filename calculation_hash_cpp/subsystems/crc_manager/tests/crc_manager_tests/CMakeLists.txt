file (GLOB SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/source/*.cc)

add_executable (crc_manager_tests ${SOURCE_FILES})

target_link_libraries (
    crc_manager_tests
    crc_manager
    doctest
    doctest_runner
    reference_data)
