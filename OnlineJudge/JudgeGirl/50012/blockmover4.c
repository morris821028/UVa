#include <stdio.h>
// #include <inttypes.h>	// standard PRIu64 output format
#include "blockmover.h"

#define VERT(x, y) (((x)<<3)|(y))
#define likely(x) __builtin_expect(!!(x), 1)
#define unlikely(x) __builtin_expect(!!(x), 0)
#define uint64_t unsigned long long
void printBlock(uint64_t *block) {
#define PRIu64 "llu"
	for (int i = 0; i < 8; i++, puts("")) {
		for (int j = 0; j < 8; j++)
			printf("%" PRIu64 "", (*block)>>(VERT(i, j))&1);
	}
#undef PRIu64
}
void initialize(uint64_t *block, int row, int col, int size) {
	uint64_t tmp = (1LLU<<size) - 1, sq = 0;
	for (int i = 0; i < size; i++)
		sq |= tmp, tmp <<= 8;
	*block = sq<<(VERT(row, col));
}
int moveLeft(uint64_t *block) {
    if (unlikely((*block) & 0x0101010101010101LLU))    return 0;
    else {
    	*block >>= 1;
    	return 1;
	}
}
int moveRight(uint64_t *block) {
    if (unlikely((*block) & 0x8080808080808080LLU))    return 0;
    else {
    	*block <<= 1;
    	return 1;
	}
}
int moveUp(uint64_t *block) {
    if (unlikely((*block) & 0x00000000000000FFLLU))    return 0;
    else {
    	*block >>= 8;
    	return 1;
	}
}
int moveDown(uint64_t *block) {
    if (unlikely((*block) & 0xFF00000000000000LLU))    return 0;
    else {
    	*block <<= 8;
    	return 1;
	}
}
#undef uint64_t
#undef VERT

// #include <stdint.h>	// standard witdth uint64_t;
#ifndef BLOCKMOVER_H

#define BLOCKMOVER_H
#define uint64_t unsigned long long
void initialize(uint64_t *block, int row, int column, int size);
void printBlock(uint64_t *block);
int moveLeft(uint64_t *block);
int moveRight(uint64_t *block);
int moveUp(uint64_t *block);
int moveDown(uint64_t *block);
#undef uint64_t
#endif // BLOCKMOVER_H


