
CXX= g++
CXXFLAGS= -g -Wall

start:
	$(CXX) $(CXXFLAGS) main.cpp astar.cpp -o main

clean:
	rm -f main *out
