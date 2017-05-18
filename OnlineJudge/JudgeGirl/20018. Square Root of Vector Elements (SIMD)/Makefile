all: main main-perf

main: main.c VSQRT.o
	gcc -Wall -std=c99 -O2 main.c VSQRT.o -o main -lm

VSQRT.o: VSQRT.c
	gcc -Wall -std=c99 -O2 VSQRT.c -c -o VSQRT.o -lm

main-perf: main-perf.c VSQRT.o
	gcc -Wall -std=c99 -O2 main-perf.c VSQRT.o -o main-perf -lm

test:
	time -p ./main

