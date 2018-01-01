cmake_minimum_required(VERSION 3.9)
project(pr_platformer)

set(CMAKE_CXX_STANDARD 11)
#set(CMAKE_VERBOSE_MAKEFILE ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pedantic -Wextra")
set(CMAKE_XCODE_ATTRIBUTE_DEBUG_INFORMATION_FORMAT "dwarf-with-dsym")

set(EXECUTABLE_OUTPUT_PATH "${PROJECT_SOURCE_DIR}/build/")
set(LIBRARY_OUTPUT_PATH "${PROJECT_SOURCE_DIR}/build/")

add_library(geometry
        SHARED
            libgeometry/src/Point.cpp
            libgeometry/src/Size.cpp
            libgeometry/src/Line.cpp
            libgeometry/src/Rect.cpp
            libgeometry/src/SpatialHash.cpp
        )

target_include_directories(geometry
        PUBLIC
            libgeometry/include
        PRIVATE
            libgeometry/src
        )

add_executable(test_libgeometry
        test-libgeometry/src/TestLibgeometry.cpp
        )

target_link_libraries(test_libgeometry
        PUBLIC
            geometry
        )

