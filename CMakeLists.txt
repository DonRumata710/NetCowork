
cmake_minimum_required(VERSION 3.5)

if (EXISTS ${CMAKE_SOURCE_DIR}/local.cmake)
    include(local.cmake)
endif()

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(NetCowork)

add_subdirectory(Generator)
add_subdirectory(NetCowork)
add_subdirectory(Tests)
add_subdirectory(Examples)
