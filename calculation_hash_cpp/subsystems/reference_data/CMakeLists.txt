set (REFERENCE_DATA_DIR ${CMAKE_CURRENT_SOURCE_DIR}/source)

file (
    GLOB
    SOURCE_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/source/*.cc
    HEADER_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/source/*.h)

add_library (reference_data STATIC ${SOURCE_FILES} ${HEADER_FILES})
target_link_libraries (reference_data)
target_include_directories (reference_data PUBLIC ${REFERENCE_DATA_DIR})
