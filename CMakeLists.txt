cmake_minimum_required(VERSION 3.3)
project(eolipile)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

include_directories($(PROJECT_SOURCE_DIR)/lib-geometry)
add_subdirectory(lib-geometry)

include_directories($(PROJECT_SOURCE_DIR)/lib-geometry-test)
add_subdirectory(lib-geometry-test)


#add_subdirectory(game)
#add_subdirectory(lib-eolipile)
#add_subdirectory(lib-eolipile-test)
