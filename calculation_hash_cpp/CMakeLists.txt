cmake_minimum_required (VERSION 3.5)

project (calculation_hash VERSION 1.0 LANGUAGES CXX)

set (CMAKE_INCLUDE_CURRENT_DIR ON)

set (CMAKE_AUTOUIC ON)
set (CMAKE_AUTOMOC ON)
set (CMAKE_AUTORCC ON)

set (CMAKE_CXX_STANDARD 17)
set (CMAKE_CXX_STANDARD_REQUIRED ON)
set (CMAKE_CXX_EXTENSIONS ON)

set (CMAKE_C_STANDARD 11)
set (CMAKE_C_STANDARD_REQUIRED ON)
set (CMAKE_C_EXTENSIONS ON)

find_package (Qt5Core)

add_executable (calculation_hash main.cc)

target_link_libraries (
    calculation_hash
    Qt5::Core
    business_logic
    input_data)

add_subdirectory ("${CMAKE_CURRENT_SOURCE_DIR}/subsystems")
add_subdirectory ("${CMAKE_CURRENT_SOURCE_DIR}/third_party")

file (MAKE_DIRECTORY /tmp/test_directory)

configure_file (
    ${CMAKE_CURRENT_SOURCE_DIR}/source_testing_files/test_file_for_read
    /tmp/test_directory/test_file_for_read COPYONLY)


set (PATH_TO_BIN /tmp/bin_calculation_hash)

install (TARGETS calculation_hash
    RUNTIME DESTINATION ${PATH_TO_BIN}
    LIBRARY DESTINATION ${PATH_TO_BIN}
    ARCHIVE DESTINATION ${PATH_TO_BIN}
    PUBLIC_HEADER DESTINATION ${PATH_TO_BIN})
