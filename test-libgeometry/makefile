# compiler and flags
CC = g++
CCFLAGS = -g -Os -std=c++11

# proper target file and directory
OUTPUTFILE = testgeometry.o
INSTALLDIR = bin/

# libgeometry
LIBGEOMBIN = ../libgeometry/bin/libgeometry.a
LIBGEOMSRC = ../libgeometry/src

# default target
.PHONY: buildall

buildall: $(OUTPUTFILE)

#each individual file and its dependency
test-libgeometry:
	$(CC) $(CCFLAGS) src/TestLibgeometry.cpp $(LIBGEOMBIN) -I $(LIBGEOMSRC) -o $(OUTPUTFILE)

$(OUTPUTFILE): test-libgeometry
	mkdir -p $(INSTALLDIR)
	cp -p  $(OUTPUTFILE) $(INSTALLDIR)
	rm *.o
	rm *.dSYM
