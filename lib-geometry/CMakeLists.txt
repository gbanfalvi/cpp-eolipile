add_library(lib-geometry STATIC src/Point.cpp src/Point.h src/Size.cpp src/Size.h src/Line.cpp src/Line.h src/Rect.cpp src/Rect.h src/SpatialHash.cpp src/SpatialHash.h src/Geometry.h)
target_include_directories(lib-geometry PUBLIC src)

