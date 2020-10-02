
cmake_minimum_required(VERSION 3.5)

project(NetCowork)

add_subdirectory(Generator)
add_subdirectory(NetCowork)
add_subdirectory(Tests)
add_subdirectory(Examples)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
