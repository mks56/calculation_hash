file (GLOB SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/source/*.cc)

add_executable (business_logic_tests ${SOURCE_FILES})

target_link_libraries (
    business_logic_tests
    business_logic
    doctest
    doctest_runner
    reference_data)
