all: main2 main3 test pin
#	gcc -std=c99 -Wall -O2 main.c -lOpenCL -fopenmp -o main
#	gcc -std=c99 -O2 test.c -lOpenCL -fopenmp -o test

main2: main2.c
	gcc -std=c99 -O2 main2.c -fopenmp -o main2 -lOpenCL

main3: main3.c
	gcc -std=c99 -O2 main3.c -o main3 -lOpenCL

test: test.c
	gcc -Wall -std=c99 -O2 test.c -lOpenCL -fopenmp -o test

pin: pin.cpp
	g++ -std=c++11 -O2 pin.cpp -o pin
