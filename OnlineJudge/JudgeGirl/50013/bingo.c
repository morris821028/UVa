#include <limits.h>
#include "bingo.h"

#define VERT(x, y) ((x)*8+(y))
int bingo(const uint64_t* board, int *rowColumn) {
	static const uint64_t lwall = 0x0101010101010101LLU;
	static const uint64_t uwall = 0x00000000000000FFLLU;
	static const uint64_t d1wall = 0x8040201008040201LLU;
	static const uint64_t d2wall = 0x0102040810204080LLU;
	uint64_t m;
	m = uwall;
	for (int i = 0; i < 8; i++) {
		if (((*board)&m) == m) {
			*rowColumn = i;
			return 1;
		}			
		m <<= 8;
	}	
	m = lwall;
	for (int i = 0; i < 8; i++) {
		if (((*board)&m) == m) {
			*rowColumn = i;
			return 2;
		}
		m <<= 1;
	}
	if (((*board)&d1wall) == d1wall) {
		*rowColumn = 0;
		return 3;
	}
	if (((*board)&d2wall) == d2wall) {
		*rowColumn = 1;
		return 3;
	}
	return 0;
}
#undef VERT
