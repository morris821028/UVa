#include <stdio.h>
// #include <inttypes.h>	// standard PRIu64 output format
#include "blockmover.h"

#define VERT(x, y) (((x)<<3)|(y))
#define likely(x) __builtin_expect(!!(x), 1)
#define unlikely(x) __builtin_expect(!!(x), 0)
#define uint64_t unsigned long long
static uint64_t sq[] = {0, 0x1, 0x303, 0x70707, 0xF0F0F0F, 0x1F1F1F1F, 0x3F3F3F3F, 0x7F7F7F7F, 0xFFFFFFFF};
inline void printBlock(uint64_t *block) {
#define PRIu64 "llu"
	for (int i = 0; i < 8; i++, puts("")) {
		for (int j = 0; j < 8; j++)
			printf("%" PRIu64 "", (*block)>>(VERT(i, j))&1);
	}
#undef PRIu64
}
inline void initialize(uint64_t *block, int row, int col, int size) {
	*block = sq[size]<<(VERT(row, col));
}
inline int moveLeft(uint64_t *block) {
    if (unlikely((*block) & 0x0101010101010101LLU))    return 0;
    else {
    	*block >>= 1;
    	return 1;
	}
}
inline int moveRight(uint64_t *block) {
    if (unlikely((*block) & 0x8080808080808080LLU))    return 0;
    else {
    	*block <<= 1;
    	return 1;
	}
}
inline int moveUp(uint64_t *block) {
    if (unlikely((*block) & 0x00000000000000FFLLU))    return 0;
    else {
    	*block >>= 8;
    	return 1;
	}
}
inline int moveDown(uint64_t *block) {
    if (unlikely((*block) & 0xFF00000000000000LLU))    return 0;
    else {
    	*block <<= 8;
    	return 1;
	}
}
#undef uint64_t
#undef VERT
