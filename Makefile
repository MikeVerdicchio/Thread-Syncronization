# Mike Verdicchio
# CS4414 - Operating Systems
# University of Virginia
# Homework 2 - Threads
# September 29, 2016

CXX = g++
CXXFLAGS = -g -std=c++11 -pthread
.SUFFIXES: .o .cpp

all: max generate

max: barrier.o max.o
	$(CXX) $(CXXFLAGS) max.o barrier.o -o max

generate: generate.o
	$(CXX) $(CXXFLAGS) generate.o -o generate
	
clean:
	/bin/rm -f *.o *~
	/bin/rm max
	/bin/rm generate

# clang++ -MM *.cpp
barrier.o: barrier.cpp
generate.o: generate.cpp
max.o: max.cpp barrier.cpp