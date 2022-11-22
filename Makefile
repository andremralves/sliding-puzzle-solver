
CXX= g++
CXXFLAGS= -g -Wall

start:
	$(CXX) $(CXXFLAGS) main.cpp limiteddfs.cpp -o main

clean:
	rm -f main *out
