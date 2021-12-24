set (INPUT_DATA_DIR ${CMAKE_CURRENT_SOURCE_DIR}/source)

file (
    GLOB
    SOURCE_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/source/*.cc
    HEADER_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/source/*.h)

add_library (input_data STATIC ${SOURCE_FILES} ${HEADER_FILES})
target_include_directories (input_data PUBLIC ${INPUT_DATA_DIR})
