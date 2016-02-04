add_library(Quadtree STATIC
        SpaceStructs.h
        SpaceStructs.cpp
        Spacehash.h
        Spacehash.cpp)

target_include_directories(Quadtree PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
