#include <limits.h>
#include "bingo.h"

#define haszero(v) (((v) - 0x0101010101010101LLU) & ~(v) & 0x8080808080808080LLU)
#define hasone(v) haszero(~v)
#define mtranspose(x, t) t = (x ^ (x >> 7)) & 0x00AA00AA00AA00AALLU; \
   x = x ^ t ^ (t << 7); \
   t = (x ^ (x >> 14)) & 0x0000CCCC0000CCCCLLU; \
   x = x ^ t ^ (t << 14); \
   t = (x ^ (x >> 28)) & 0x00000000F0F0F0F0LLU; \
   x = x ^ t ^ (t << 28);
#define VERT(x, y) ((x)*8+(y))
int bingo(const uint64_t* board, int *rowColumn) {
	static const uint64_t d1wall = 0x8040201008040201LLU;
	static const uint64_t d2wall = 0x0102040810204080LLU;
	uint64_t m, x = *board, t;
	m = hasone(x);
	if (m) {
		*rowColumn = __builtin_ctzll(m)>>3;
		return 1;
	}
	mtranspose(x, t);
	m = hasone(x);
	if (m) {
		*rowColumn = __builtin_ctzll(m)>>3;
		return 2;
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
