INCLUDE=../utils

all: main

main: main.cu lab3.o pgm.o
	nvcc --compiler-options -Wall -I$(INCLUDE) -arch sm_30 -std=c++11 -O2 main.cu lab3.o pgm.o -o main

lab3.o: lab3.cu
	nvcc --compiler-options -Wall -I$(INCLUDE) -arch sm_30 -std=c++11 -O2 lab3.cu -c -o lab3.o

pgm.o: pgm.cpp
	nvcc --compiler-options -Wall -I$(INCLUDE) -arch sm_30 -std=c++11 -O2 pgm.cpp -c -o pgm.o

test:
	perf stat ./main img_background.ppm img_target.ppm img_mask.pgm 130 600 output.ppm
	python ppm2jpg.py

diff:
	python ./diff-img.py output.jpg output-standard.jpg

server:
	python -m SimpleHTTPServer 8888
