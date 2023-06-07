
set(APPLICATION_NAME Generator)

set(SOURCE_DIR ${PROJECT_SOURCE_DIR}/${APPLICATION_NAME}/)

set(CLASSES
    class
    codeelement
    dependency
    enum
    filehandler
    function
    interfacemodel
    printer
    property
    simpletypeelement
    struct
    types
)

set(HEADERS)

set(SOURCES
	main.cpp
)

foreach(class ${CLASSES})
    LIST(APPEND SOURCES ${SOURCE_DIR}${class}.cpp)
    LIST(APPEND HEADERS ${SOURCE_DIR}${class}.h)
endforeach()

foreach(header ${UTILITY_HEADERS})
    LIST(APPEND HEADERS ${SOURCE_DIR}${header}.h)
endforeach()

function(generate_parser input_file source_files header_dir)
    if ("${REFLEX_PATH}" STREQUAL "")
        message(FATAL_ERROR "No path to Re-flex")
    endif()

    if ("${BISON_PATH}" STREQUAL "")
        message(FATAL_ERROR "No path to bison")
    endif()

    cmake_path(GET input_file FILENAME input_file_name)
    set(OUT_DIR "${CMAKE_CURRENT_BINARY_DIR}/generated/")

    set(LEXER_FILE ${input_file}.lxx)
    set(LEXER_HEADER_FILE ${OUT_DIR}${input_file_name}.lexer.hpp)
    set(LEXER_SOURCE_FILE ${OUT_DIR}${input_file_name}.lexer.cpp)

    add_custom_command(
        OUTPUT ${LEXER_HEADER_FILE} ${LEXER_SOURCE_FILE}
        COMMAND ${REFLEX_PATH}/bin/reflex.exe ${LEXER_FILE} --outfile=${LEXER_SOURCE_FILE} --header-file=${LEXER_HEADER_FILE}
        DEPENDS ${LEXER_FILE}
        WORKING_DIRECTORY "${OUT_DIR}"
    )

    set(PARSE_FILE ${input_file}.yxx)
    set(PARSE_HEADER_FILE ${OUT_DIR}${input_file_name}.parser.hpp)
    set(PARSE_SOURCE_FILE ${OUT_DIR}${input_file_name}.parser.cpp)

    add_custom_command(
        OUTPUT ${PARSE_HEADER_FILE} ${PARSE_SOURCE_FILE}
        COMMAND ${BISON_PATH} -d ${PARSE_FILE} --output=${PARSE_SOURCE_FILE}
        DEPENDS ${PARSE_FILE}
        WORKING_DIRECTORY "${OUT_DIR}"
    )

    string(JOIN ";" ${source_files} ${LEXER_HEADER_FILE} ${LEXER_SOURCE_FILE} ${PARSE_HEADER_FILE} ${PARSE_SOURCE_FILE})
    set(${source_files} ${${source_files}} PARENT_SCOPE)
    set(${header_dir} ${OUT_DIR} PARENT_SCOPE)
endfunction()

generate_parser(${CMAKE_CURRENT_SOURCE_DIR}/interface generated_sources generated_headers_dir)
message("generated files: ${generated_sources}")

set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH};${REFLEX_PATH})
find_package(reflex COMPONENTS ReflexLibStatic REQUIRED)

list(APPEND SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/interface.yxx")
list(APPEND SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/interface.lxx")

add_executable(${APPLICATION_NAME} ${HEADERS} ${generated_sources} ${SOURCES})

target_link_libraries(${APPLICATION_NAME} PUBLIC Reflex::ReflexLibStatic)

target_include_directories(${APPLICATION_NAME} PRIVATE ${generated_headers_dir})
target_include_directories(${APPLICATION_NAME} PRIVATE ${SOURCE_DIR})

install(TARGETS ${APPLICATION_NAME} DESTINATION bin)
