all:  test test-clang-sse test-clang-avx test-sse test-avx pin

test: test.c
	gcc -Wall -std=c99 -O3 -march=native test.c -o test

test-clang-sse: test.c
	clang-3.8 -Wall -std=c99 -O3 -march=native test-sse.c -o test-clang-sse

test-clang-avx: test.c
	clang-3.8 -Wall -std=c99 -O3 -march=native test-avx.c -o test-clang-avx

test-sse: test-sse.c
	gcc -Wall -std=c99 -O3 -march=native test-sse.c -o test-sse

test-avx: test-avx.c
	gcc -Wall -std=c99 -O3 -march=native test-avx.c -o test-avx


pin: pin.cpp
	g++ -std=c++11 -O2 pin.cpp -o pin
