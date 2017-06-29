all: main main-perf

main: main.c DRS.o
	gcc -std=c99 -O2 -march=native main.c DRS.o -o main

DRS.o: DRS.h DRS.c
	gcc -std=c99 -O2 -march=native DRS.c -c -o DRS.o

main-perf: main-perf.c DRS.o
	gcc -std=c99 -O2 -march=native main-perf.c DRS.o -o main-perf


