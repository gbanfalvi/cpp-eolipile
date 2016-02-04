add_library(lib-geometry STATIC Point.cpp Point.h Size.cpp Size.h Line.cpp Line.h Rect.cpp Rect.h SpatialHash.cpp SpatialHash.h Geometry.h)

target_include_directories(lib-geometry PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
