CXX=g++
OBJ=loader_sym

.PHONY: all clean

all: $(OBJ)

loader.o: ./loader.cc
	$(CXX) -std=c++11 -c ./loader.cc

loader_sym: loader.o loader_sym.cc
	$(CXX) -std=c++11 -o loader_sym loader_sym.cc loader.o -lbfd

clean:
	rm -f $(OBJ) *.o

