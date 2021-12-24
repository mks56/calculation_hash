set (FILE_MANAGER_DIR ${CMAKE_CURRENT_SOURCE_DIR}/source)

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

find_package (Boost 1.65.1 REQUIRED COMPONENTS filesystem thread)
include_directories (${Boost_INCLUDE_DIRS})

add_library (file_manager SHARED ${SOURCE_FILES} ${HEADER_FILES})
target_link_libraries (file_manager PUBLIC ${Boost_LIBRARIES} exceptions
                                           reference_data)
target_include_directories (
    file_manager
    PUBLIC ${Boost_INCLUDE_DIRS}
           ${FILE_MANAGER_DIR}
           exceptions
           reference_data)

set (PATH_TO_LIB /tmp/business_logic)

install (TARGETS file_manager
      RUNTIME DESTINATION ${PATH_TO_LIB}
      LIBRARY DESTINATION ${PATH_TO_LIB}
)
