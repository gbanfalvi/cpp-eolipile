# compiler and flags
CC = g++
CCFLAGS = -g -Os -std=c++11 -c

# proper target file and directory
OUTPUTFILE = libgeometry.a
INSTALLDIR = bin/

# default target
.PHONY: buildall

buildall: $(OUTPUTFILE)

#each individual file and its dependency
Size.o: src/Size.hpp
	$(CC) $(CCFLAGS) src/Size.cpp

Point.o: src/Point.hpp
	$(CC) $(CCFLAGS) src/Point.cpp

Line.o: src/Line.hpp Point.o
	$(CC) $(CCFLAGS) src/Line.cpp

Rect.o: src/Rect.hpp Line.o Point.o
	$(CC) $(CCFLAGS) src/Rect.cpp

SpatialHash.o: src/SpatialHash.hpp Rect.o Line.o Point.o Size.o
	$(CC) $(CCFLAGS) src/SpatialHash.cpp

$(OUTPUTFILE): SpatialHash.o Rect.o Line.o Point.o Size.o
	ar rcsv $@ $^
	ranlib $@
	mkdir -p $(INSTALLDIR)
	cp -p  $(OUTPUTFILE) $(INSTALLDIR)
	rm *.o
	rm *.a
