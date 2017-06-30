CXX=g++
CFLAGS=-std=c++11 -O2

all: brute brute-opt pin rtree

brute: brute.cpp
	$(CXX) $(CFLAGS) $^ -o $@

brute-opt: brute-opt.cpp
	$(CXX) $(CFLAGS) $^ -o $@

rtree: rtree.cpp
	$(CXX) $(CFLAGS) $^ -o $@
	
pin: pin.cpp
	$(CXX) $(CFLAGS) $^ -o $@

clean:
	rm block brute pin rtree
