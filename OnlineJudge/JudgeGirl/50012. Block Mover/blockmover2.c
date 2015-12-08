#include <stdio.h>
// #include <inttypes.h>	// standard PRIu64 output format
#include "blockmover.h"

#define VERT(x, y) (((x)<<3)|(y))
#define likely(x) __builtin_expect(!!(x), 1)
#define unlikely(x) __builtin_expect(!!(x), 0)
#define uint64_t unsigned long long
static uint64_t sq[] = {0x1, 0x303, 0x70707, 0xF0F0F0F, 0x1F1F1F1F, 0x3F3F3F3F, 0x7F7F7F7F, 0xFFFFFFFF};
void printBlock(uint64_t *block) {
#define PRIu64 "llu"
	for (int i = 0; i < 8; i++, puts("")) {
		for (int j = 0; j < 8; j++)
			printf("%" PRIu64 "", (*block)>>(VERT(i, j))&1);
	}
#undef PRIu64
}
void initialize(uint64_t *block, int row, int col, int size) {
	*block = sq[size]<<(VERT(row, col));
}
int moveLeft(uint64_t *block) {
	uint64_t v = *block;
	for (int i = 0; i < 8; i++) {
		if (v & (1LLU<<VERT(i, 0)))
			return 0;
	}
	*block >>= 1;
	return 1;
}
int moveRight(uint64_t *block) {
	uint64_t v = *block;
	for (int i = 0; i < 8; i++) {
		if (v & (1LLU<<VERT(i, 7)))
			return 0;
	}
	*block <<= 1;
	return 1;
}
int moveUp(uint64_t *block) {
	uint64_t v = *block;
	for (int i = 0; i < 8; i++) {
		if (v & (1LLU<<VERT(0, i)))
			return 0;
	}
    *block >>= 8;
    return 1;
}
int moveDown(uint64_t *block) {
	uint64_t v = *block;
	for (int i = 0; i < 8; i++) {
		if (v & (1LLU<<VERT(7, i)))
			return 0;
	}
	*block <<= 8;
	return 1;
}
#undef uint64_t
#undef VERT
