all: main main-own main-test

labeling.o: labeling.cu
	nvcc -arch sm_30 -Xcompiler "-O2 -fopenmp" -c labeling.cu -o labeling.o

labeling-own.o: labeling-own.cu
	nvcc -arch sm_30 -Xcompiler "-O2 -fopenmp" -O2 -c labeling-own.cu -o labeling-own.o

labeling-test.o: labeling-test.cu
	nvcc -arch sm_30 -Xcompiler "-O2 -fopenmp" -O2 -c labeling-test.cu -o labeling-test.o


main: main.cu labeling.o
	nvcc -arch sm_30 -Xcompiler "-O2 -fopenmp" -O2 main.cu labeling.o -o main

main-own: main.cu labeling-own.o
	nvcc -arch sm_30 -Xcompiler "-O2 -fopenmp" -O2 main.cu labeling-own.o -o main-own

main-test: main.cu labeling-test.o
	nvcc -arch sm_30 -Xcompiler "-O2 -fopenmp" -O2 main.cu labeling-test.o -o main-test




