all: main pin

main: main.cu
	nvcc -arch sm_30 -Xcompiler "-O2 -fopenmp" main.cu -o main

pin: pin.cpp
	g++ -std=c++11 -O2 pin.cpp -o pin
