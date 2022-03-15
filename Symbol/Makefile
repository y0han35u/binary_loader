CXX=g++
OBJ=loader_demo

.PHONY: all clean

all: $(OBJ)

loader.o: ./loader.cc
	$(CXX) -std=c++11 -c ./loader.cc

loader_demo: loader.o loader_demo.cc
	$(CXX) -std=c++11 -o loader_demo loader_demo.cc loader.o -lbfd

loader_xdd: loader.o loader_xdd.cc
	$(CXX) -std=c++11 -o loader_xdd loader_xdd.cc loader.o -lbfd

clean:
	rm -f $(OBJ) *.o

