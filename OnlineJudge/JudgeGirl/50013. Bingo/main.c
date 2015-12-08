#include <stdio.h>
#include <assert.h>
#include "bingo.h"

#define VERT(x, y) ((x)*8+(y))
void printBlock(unsigned long long const *block) {
	for (int i = 0; i < 8; i++, puts("")) {
		for (int j = 0; j < 8; j++)
			printf("%llu", (*block)>>(VERT(i, j))&1);
	}
}
#undef VERT
#define hash(x) ((x) * 2654435761LU)

int main() {
#define VERT(x, y) ((x)*8+(y))
	int spec, step, seed;
	while (scanf("%d", &spec) == 1) {
		unsigned long long g = 0;
		if (spec == 1) {
			int bidx = -1, ret;
			g = 255LLU<<56;
			ret = bingo(&g, &bidx);
			printf("%d %d\n", ret, bidx);
		} else if (spec == 2) {
			int bidx = -1, ret, x;
			scanf("%d", &x);
			g = 255LLU<<(x * 8);
			ret = bingo(&g, &bidx);
			printf("%d %d\n", ret, bidx);
		} else if (spec == 3) {
			scanf("%d %d", &step, &seed);
			int x, bidx, r;
			unsigned long long mra = seed, ret = seed;
			for (int i = 0; i < step; i++) {
				mra = hash(mra + i);
				x = mra&7;
				g = 255LLU<<(x * 8);
				bidx = 0, r = bingo(&g, &bidx);
				ret = hash(ret + r);
				ret = hash(ret + bidx);
			}
			printf("%llu\n", ret);
		} else if (spec == 4) {
			int x, bidx = -1, ret;
			scanf("%d", &x);
			g = 0x0101010101010101LLU<<x;
			ret = bingo(&g, &bidx);
			printf("%d %d\n", ret, bidx);
		} else if (spec == 5) {
			scanf("%d %d", &step, &seed);
			int bidx, r;
			unsigned long long mra = seed, ret = seed;
			unsigned long long center1 = 1LLU<<VERT(3, 3);
			unsigned long long center2 = 1LLU<<VERT(4, 3);
			for (int i = 0; i < step; i++) {
				mra = hash(mra + i);
				g = mra;
				g ^= g&center1;
				g ^= g&center2;
				bidx = 0, r = bingo(&g, &bidx);
				ret = hash(ret + r);
				ret = hash(ret + bidx);
			}
			printf("%llu\n", ret);
		} else if (spec == 6) {
			scanf("%d %d", &step, &seed);
			int bidx, r;
			unsigned long long mra = seed, ret = seed;
			for (int i = 0; i < step; i++) {
				mra = hash(mra + i);
				g = mra;
				bidx = 0, r = bingo(&g, &bidx);
				ret = hash(ret + r);
				ret = hash(ret + bidx);
			}
			printf("%llu\n", ret);
		}
	}
//	uint64_t g = 0;
//	for (int i = 0; i < 8; i++) {
//		char s[16];
//		scanf("%s", s);
//		for (int j = 0; j < 8; j++)
//			if (s[j] == '1')
//				g |= 1LLU<<VERT(i, j);
//	}
//	int bidx = -1, ret;
//	ret = bingo(&g, &bidx);
//	printf("%d %d\n", ret, bidx);
#undef VERT
	return 0;
}
/*
// Part 1

// 1.in
1

// Part 2

// 2.in
2
5

// 3.in
2
6

// Part 3

// 4.in
3
1000000 520

// 5.in
3
1000000 514

// 6.in
3
1000000 1024

// 7.in
3
1000000 1

// Part 4

// 8.in
4
5

// 9.in
4
7

// Part 5

// 10.in
5
1000000 514

// 11.in
5
1000000 1

// 12.in
5
1000000 100007

// 13.in
5
20000000 100009

// 14.in
5
20000000 1048576

// 15.in
5
20000000 0

// 16.in
5
20000000 124128

// Part 6

// 17.in
6
20000000 987

// 18.in
6
20000000 6541

// 19.in
6
20000000 12598

*/
/*
00100100
00000100
11000100
01111111
00110100
01000100
01000100
00000100

10000000
01000000
00100000
00010000
00001000
00000100
00000010
00000001

00000001
00000010
00000100
00001000
00010000
00100000
01000000
10000000
*/
