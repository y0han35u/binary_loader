CXX=g++
OBJ=loader_demo loader_xdd

.PHONY: all clean

all: $(OBJ)

loader.o: ./inc/loader.cc
	$(CXX) -std=c++11 -c ./inc/loader.cc

loader_demo: loader.o loader_demo.cc
	$(CXX) -std=c++11 -o loader_demo loader_demo.cc loader.o -lbfd

loader_xdd: loader.o loader_xdd.cc
	$(CXX) -std=c++11 -o $@ $^ -lbfd

clean:
	rm -f $(OBJ) *.o

