set (EXCEPTIONS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/source)

file (
    GLOB
    SOURCE_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/source/*.cc
    HEADER_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/source/*.h)

add_library (exceptions SHARED ${SOURCE_FILES} ${HEADER_FILES})
target_link_libraries (exceptions)
target_include_directories (exceptions PUBLIC ${EXCEPTIONS_DIR})

set (PATH_TO_LIB /tmp/business_logic)

install (TARGETS exceptions
       RUNTIME DESTINATION ${PATH_TO_LIB}
       LIBRARY DESTINATION ${PATH_TO_LIB}
)
