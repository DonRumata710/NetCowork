
set(LIBRARY_NAME NetCowork)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Core Network REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core Network REQUIRED)

set(HEADER_DIR ${PROJECT_SOURCE_DIR}/include/)
set(SOURCE_DIR ${PROJECT_SOURCE_DIR}/${LIBRARY_NAME}/)

set(CLASSES
    message
    netcoworkclient
    netcoworker
    netcoworkfactory
    netcoworkprovider
    netcoworkserver
)

set(HEADERS)
set(SOURCES)

include_directories(${HEADER_DIR})
include_directories(${Qt${QT_VERSION_MAJOR}Core_INCLUDE_DIRS}/..)
include_directories(${Qt${QT_VERSION_MAJOR}Core_INCLUDE_DIRS})
include_directories(${Qt${QT_VERSION_MAJOR}Network_INCLUDE_DIRS})

foreach(class ${CLASSES})
    LIST(APPEND SOURCES ${SOURCE_DIR}${class}.cpp)
    LIST(APPEND HEADERS ${HEADER_DIR}${class}.h)
endforeach()

add_library(${LIBRARY_NAME} ${SOURCES} ${HEADERS})

target_link_libraries(${LIBRARY_NAME} PUBLIC
    Qt::Core
    Qt::Network
)
