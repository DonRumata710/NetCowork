
set(APPLICATION_NAME Example1)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Core Network Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core Network Widgets REQUIRED)

set(SOURCE_DIR ${PROJECT_SOURCE_DIR}/Examples/${APPLICATION_NAME}/)

set(NC_FILES
    netobject
)

set(FORMS
    mainwindow
)

set(HEADERS)

set(UI_FILES)

set(SOURCES
	main.cpp
)

foreach(form ${FORMS})
    LIST(APPEND SOURCES ${SOURCE_DIR}${form}.cpp)
    LIST(APPEND HEADERS ${SOURCE_DIR}${form}.h)
    LIST(APPEND UI_FILES ${SOURCE_DIR}${form}.ui)
endforeach()

foreach(class ${CLASSES})
    LIST(APPEND SOURCES ${SOURCE_DIR}${class}.cpp)
    LIST(APPEND HEADERS ${SOURCE_DIR}${class}.h)
endforeach()

foreach(header ${UTILITY_HEADERS})
    LIST(APPEND HEADERS ${SOURCE_DIR}${header}.h)
endforeach()

foreach(gen_file ${NC_FILES})
    add_custom_command(
        OUTPUT  ${CMAKE_CURRENT_BINARY_DIR}/generated/${gen_file}.h
        PRE_BUILD
        COMMAND ${PROJECT_BINARY_DIR}/Generator/Generator -i ${SOURCE_DIR}/${gen_file}.nc -o ${CMAKE_CURRENT_BINARY_DIR}/generated
        DEPENDS ${gen_file}.nc
    )
    LIST(APPEND HEADERS ${CMAKE_CURRENT_BINARY_DIR}/generated/${gen_file}.h)
    LIST(APPEND RES_FILES ${gen_file}.nc)
endforeach()

include_directories(${PROJECT_SOURCE_DIR}/include ${CMAKE_CURRENT_BINARY_DIR} ${SOURCE_DIR})
add_executable(${APPLICATION_NAME} ${SOURCES} ${HEADERS} ${UI_FILES} ${RES_FILES})

target_link_libraries(${APPLICATION_NAME} PRIVATE NetCowork Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Network Qt${QT_VERSION_MAJOR}::Widgets)

install(TARGETS ${APPLICATION_NAME} DESTINATION bin)
