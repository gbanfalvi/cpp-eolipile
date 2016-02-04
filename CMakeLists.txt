cmake_minimum_required(VERSION 3.3)
project(eolipile)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

add_subdirectory(lib-geometry)
add_subdirectory(lib-geometry-test)

