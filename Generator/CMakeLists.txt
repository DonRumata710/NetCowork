
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
	parser
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

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

foreach(class ${CLASSES})
    LIST(APPEND SOURCES ${SOURCE_DIR}${class}.cpp)
    LIST(APPEND HEADERS ${SOURCE_DIR}${class}.h)
endforeach()

foreach(header ${UTILITY_HEADERS})
    LIST(APPEND HEADERS ${SOURCE_DIR}${header}.h)
endforeach()

include_directories(${SOURCE_DIR})
add_executable(${APPLICATION_NAME} ${SOURCES} ${HEADERS})

install(TARGETS ${APPLICATION_NAME} DESTINATION bin)
