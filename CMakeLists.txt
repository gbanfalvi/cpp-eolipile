cmake_minimum_required(VERSION 3.9)
project(pr_platformer)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_VERBOSE_MAKEFILE ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pedantic -Wextra -v")
set(CMAKE_XCODE_ATTRIBUTE_DEBUG_INFORMATION_FORMAT "dwarf-with-dsym")

set(EXECUTABLE_OUTPUT_PATH "${PROJECT_SOURCE_DIR}/build/")
set(LIBRARY_OUTPUT_PATH "${PROJECT_SOURCE_DIR}/build/")

# libgeometry

add_library(geometry
        STATIC
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

# test libgeometry

add_executable(test_libgeometry
        test-libgeometry/src/TestLibgeometry.cpp
        test-libgeometry/src/Testing.h)

target_link_libraries(test_libgeometry
        PUBLIC
            geometry
        )

# sdl2 & sdl2_image

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/libsdl")

set(SDL2_PATH libsdl)          # Apple only?
set(SDL2_IMAGE_PATH libsdl)

find_package(SDL2 REQUIRED)
find_package(SDL2_IMAGE REQUIRED)

include_directories(${SDL2_INCLUDE_DIR}) #Ugly
include_directories(${SDL2_IMAGE_INCLUDE_DIR})



# libeolipile

add_library(eolipile
        STATIC
            libeolipile/src/EngineDimensions.cpp
            libeolipile/src/EngineInputListener.cpp
            libeolipile/src/EngineInputHandler.cpp
            libeolipile/src/EngineSprite.cpp
            libeolipile/src/EngineItemState.cpp
            libeolipile/src/EngineItem.cpp
            libeolipile/src/EngineWorld.cpp
            libeolipile/src/GameEngine.cpp

        )

target_link_libraries(eolipile
        PUBLIC
            geometry
            ${SDL2_LIBRARY}
            ${SDL2_IMAGE_LIBRARIES}
        )

target_include_directories(eolipile
        PUBLIC
            libeolipile/src
        #    libgeometry/src
        )

# test libeolipile

add_executable(test_libeolipile
        test-libeolipile/src/Test.cpp
        )

target_link_libraries(test_libeolipile
        PRIVATE
            eolipile
            ${SDL2_LIBRARY}
            ${SDL2_IMAGE_LIBRARIES})

IF(APPLE)

    add_custom_command(TARGET eolipile POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_SOURCE_DIR}/${SDL2_PATH}/SDL2.framework
            ${PROJECT_SOURCE_DIR}/build/SDL2.framework
            )

    add_custom_command(TARGET eolipile POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_SOURCE_DIR}/${SDL2_PATH}/SDL2_image.framework
            ${PROJECT_SOURCE_DIR}/build/SDL2_image.framework
            )

    link_directories(${PROJECT_SOURCE_DIR}/build)

ENDIF(APPLE)


message(STATUS ${SDL2_PATH})