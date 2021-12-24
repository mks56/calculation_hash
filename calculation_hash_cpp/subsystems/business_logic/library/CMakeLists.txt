set (BUSINESS_LOGIC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/source)

file (
    GLOB
    SOURCE_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/source/*.cc
    HEADER_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/source/*.h)

set (BOOST_ROOT "/usr/lib/x86_64-linux-gnu/")
set (Boost_USE_STATIC_IBS OFF)
set (Boost_USE_MULTITHREADED ON)
set (Boost_USE_STATIC_RUNTIME OFF)

find_package (Boost 1.65.1 REQUIRED COMPONENTS thread)
include_directories (${Boost_INCLUDE_DIRS})

add_library (business_logic SHARED ${SOURCE_FILES} ${HEADER_FILES})

target_include_directories(business_logic PUBLIC ${HEADER_FILES})


target_link_libraries (
    business_logic
    PUBLIC ${Boost_LIBRARIES}
           crc_manager
           exceptions
           file_manager
           reference_data)
target_include_directories (
    business_logic
    PUBLIC ${Boost_INCLUDE_DIRS}
           ${BUSINESS_LOGIC_DIR}
           crc_manager
           exceptions
           file_manager
           reference_data)

set (PATH_TO_LIB /tmp/business_logic)
set (HEADERS  ${CMAKE_CURRENT_SOURCE_DIR}/source/c_basic_functional.h)

set_target_properties (business_logic PROPERTIES PUBLIC_HEADER "${HEADERS}")

install (TARGETS business_logic
        RUNTIME DESTINATION ${PATH_TO_LIB}
        LIBRARY DESTINATION ${PATH_TO_LIB}
        ARCHIVE DESTINATION ${PATH_TO_LIB}
        PUBLIC_HEADER DESTINATION ${PATH_TO_LIB}
        PRIVATE_HEADER DESTINATION ${PATH_TO_LIB}
        INCLUDES DESTINATION ${PATH_TO_LIB})
