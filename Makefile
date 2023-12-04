# Makefile

CXX_FLAGS = -Wall --std=c++20 -g

all: runMovies

runMovies: main.o movies.o 
	g++ $(CXX_FLAGS) -o runMovies main.o movies.o 
main.o: main.cpp movies.o
	g++ -c $(CXX_FLAG) main.cpp
movies.o: movies.cpp
	g++ -c $(CXX_FLAG) movies.cpp 
clean:
	rm -f runMovies *.o