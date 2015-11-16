#include <stdio.h>
#include <assert.h>
#include "blockmover.h"

#define hash(x) ((x) * 2654435761LU)

#define VERT(x, y) (((x)<<3)+(y))
#define uint64_t unsigned long long
void m_initialize(uint64_t *block, int row, int col, int size) {
	*block = 0;
	for (int i = row; i < row+size; i++) {
		for (int j = col; j < col+size; j++) 
			*block |= 1LLU<<VERT(i, j);
	}
}
#undef uint64_t
#undef VERT

int main() {
	int (*FUNC[]) (unsigned long long*) = {moveLeft, moveRight, moveUp, moveDown};
	int dir[128] = {['a'] = 0, ['d'] = 1, ['w'] = 2, ['s'] = 3};
	int x, y, sz;
	int spec, step, seed;
	char cmd[128];
	unsigned long long board = -1, tboard = -1;
		
	while (scanf("%d %d %d", &x, &y, &sz) == 3) {
		scanf("%d %d %d", &spec, &step, &seed);
		initialize(&board, x, y, sz);
		initialize(&tboard, 3, 3, 1);
		
		unsigned long long mra = seed, ret = seed;
		if (spec == 1) {	
			m_initialize(&board, x, y, sz);
			// 20pt. implement printBlock
		} else if (spec == 2) {
			// 15pt. implement printBlock, moveLeft, and moveRight
			m_initialize(&board, x, y, sz);
			for (int i = 0, dir, r; i < step; i++) {
				mra = hash(mra + i);
				dir = mra&1;
				r = FUNC[dir](&board);
				ret = hash(ret + r);
				FUNC[dir](&tboard);
				assert(r == 1);
			}
		} else if (spec == 3) {
			// 20pt. implement printBlock, and all four move funnctions. All moves are valid.
			m_initialize(&board, x, y, sz);
			for (int i = 0, dir, r; i < step; i++) {
				mra = hash(mra + i);
				dir = mra&3;
				r = FUNC[dir](&board);
				ret = hash(ret + r);
				FUNC[dir](&tboard);
				assert(r == 1);
				printf("%d\n", dir);
			}
		} else if (spec == 4) {
			// 30pt. implement all four move and initilize functions. All moves are valid.
			for (int i = 0, dir, r; i < step; i++) {
				mra = hash(mra + i);
				dir = mra&3;
				r = FUNC[dir](&board);
				ret = hash(ret + r);
				FUNC[dir](&tboard);
				assert(r == 1);
				printf("%d\n", dir);
			}
		} else if (spec == 5) {
			// 15pt. implement all four move and initilize functions. Some moves may be invalid.
			for (int i = 0, dir, r; i < step; i++) {
				mra = hash(mra + i);
				dir = (mra>>6)&3;
				r = FUNC[dir](&board);
				ret = hash(ret + r);
				FUNC[dir](&tboard);
			}
		}
		printBlock(&board);
		printf("%llu %llu\n", mra, ret);
		
		// waste time
		if (spec >= 2) {
			for (int i = 0; i < 10000000; i++) {
				initialize(&tboard, 0, 0, 8);
			}
			for (int i = 0; i < 10000000; i++) {
				initialize(&tboard, 3, 3, 1);
			}
			for (int i = 0; i < 40000000; i++) {
				FUNC[0](&tboard);
				FUNC[1](&tboard);
			}
			if (spec >= 3) {
				for (int i = 0; i < 10000000; i++) {
					FUNC[2](&tboard);
					FUNC[3](&tboard);
				}
			}
		}
	}
	
//	while (scanf("%1s", cmd) == 1) {
//		switch(cmd[0]) {
//			case 'w':case 'a':case 's':case 'd': {
//				int ret = FUNC[dir[cmd[0]]](&board);
//				if (ret == 1)
//					puts("MOVE SUCCESS");
//				else
//					puts("MOVE FAIL");
//				break;
//			}
//			default:
//				puts("INVALID COMMAND");
//		}
//		printBlock(&board);
//		puts("========");
//	} 
	return 0;
}
/*
// Part 1

// 1.in
4 4 4
1 0 1

// 2.in
0 0 8
1 0 1

// 3.in
0 6 2
1 0 1

// 4.in
2 0 5
1 0 1

// Part 2

// 5.in
3 3 2
2 3 2

// 6.in
3 3 3
2 3 4

// 7.in
3 3 2
2 4 5

// Part 3

// 8.in
2 3 3
3 10 5

// 9.in
2 3 4
3 10 512

// 10.in
2 2 5
3 20 1259

// 11.in
2 2 6
3 2 122

// Part 4

// 12.in
6 6 1
4 20 124

// 13.in
6 3 2
4 6 5566

// 14.in
0 2 4
4 4 7744

// 15.in
2 3 2
4 30 124125

// 16.in
1 3 3
4 30 124125125

// 17.in
6 0 1
4 5 1

// Part 5

// 18.in
3 3 4
5 20000000 188

// 19.in
2 4 3
5 20000000 402

// 20.in
0 0 3
5 10000000 1
1 1 6
5 5000000 2
1 1 7
5 5000000 3
*/
