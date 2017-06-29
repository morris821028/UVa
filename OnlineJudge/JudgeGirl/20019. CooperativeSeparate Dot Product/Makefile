all: main2 main3 test pin main-task
#	gcc -std=c99 -Wall -O2 main.c -lOpenCL -fopenmp -o main
#	gcc -std=c99 -O2 test.c -lOpenCL -fopenmp -o test

main2: main2.c
	gcc -std=c99 -O2 main2.c -fopenmp -o main2 -lOpenCL

main3: main3.c
	gcc -Wall -std=c99 -O2 main3.c -fopenmp -o main3 -lOpenCL

main-task: main-task.c
	gcc -Wall -std=c99 -O2 main-task.c -fopenmp -o main-task -lOpenCL


test: test.c
	gcc -Wall -std=c99 -O2 -msse -mavx test.c -fopenmp -o test
	gcc -Wall -std=c99 -O2 -msse -mavx test.c -fopenmp -o test-sse

pin: pin.cpp
	g++ -std=c++11 -O2 pin.cpp -o pin
