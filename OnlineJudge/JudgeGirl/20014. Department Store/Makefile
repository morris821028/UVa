all: main pin main2

main: main.c
	gcc -std=c99 -O2 main.c -o main

main2: main2.c
	gcc -std=c99 -O2 main2.c -o main2


pin: pin.cpp
	g++ -std=c++11 -O2 pin.cpp -o pin

clean: 
	rm main pin
