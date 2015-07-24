#include <bits/stdc++.h>
#pragma GCC optimize ("O3")
using namespace std;

//const int dx[] = {-3, -3, -2, -1, 0, 1, 2, 3, 3, 3, 2, 1, 0, -1, -2, -3};
//const int dy[] = {0, 1, 2, 3, 3, 3, 2, 1, 0, -1, -2, -3, -3, -3, -2, -1};
#define MAXH 2048
#define MAXW 2048
char g[MAXH][MAXW], ret[MAXH*MAXW];
char *ptr_g;
int n, m;
#define AB00  -3*MAXW 
#define AB01  -3*MAXW+1
#define AB02  -2*MAXW+2
#define AB03  -MAXW+3
#define AB40  3
#define AB41  MAXW+3
#define AB42  2*MAXW+2
#define AB43  3*MAXW+1
#define AB80  3*MAXW
#define AB81  3*MAXW-1
#define AB82  2*MAXW-2
#define AB83  MAXW-3
#define AB120 -3
#define AB121 -MAXW-3
#define AB122 -2*MAXW-2
#define AB123 -3*MAXW-1
#define T(x, y, z, w) (*(ptr_g + AB##z##w)<<(z+w)) 
#define UNLOOPX(i) ((val&cor[i]) == cor[i] || (val&cor[i+1]) == cor[i+1] || \
 					(val&cor[i+2]) == cor[i+2] || (val&cor[i+3]) == cor[i+3]) 
#define UNLOOPXALL UNLOOPX(0) || UNLOOPX(4) || UNLOOPX(8) || UNLOOPX(12)
#define UNLOOPY(i) T(x, y, i, 0) | T(x, y, i, 1) | T(x, y, i, 2) | T(x, y, i, 3) 
#define UNLOOPYALL UNLOOPY(0) | UNLOOPY(4) | UNLOOPY(8) | UNLOOPY(12)
typedef unsigned short int UINT16;
UINT16 cor[16] = {};
UINT16 rotate_left(UINT16 x, UINT16 n) {
	return  (x << n) | (x >> (16-n));
}
char f[1<<16];
int main() {
	UINT16 val;
	for (int i = 0, j = (1<<12)-1; i < 16; i++, j = rotate_left(j, 1))
		cor[i] = j;
	for (int i = 0, one; i < 1<<16; i++) {
		val = i, one = __builtin_popcount(val);
		if (one < 12 && one > 4)
			f[i] = 0;
		else
			f[i] = UNLOOPXALL ? 1 : (val = ~val, UNLOOPXALL);
		f[i] |= '0';
	}
	int cases = 0;
	char c;
	while (scanf("%d %d", &n, &m) == 2) {
		while (getchar() != '\n');
		for (int i = 0; i < n; i++) {
			fgets(g[i], 2000, stdin);
			for (int j = 0; j < m; j++)
				g[i][j] -= '0';
		}
		int bn = n-3, bm = m-3;
		char *p = ret;
		for (int i = 0; i < 3; i++) {
			memset(p, '0', m), p += m;
			*p = '\n', p++;
		}
		for (int x = 3, y; x < bn; x++) {
			*p = '0', p++, *p = '0', p++, *p = '0', p++;
			ptr_g = g[x]+3;
#define UNLOOP { \
	val = UNLOOPYALL; \
	*p = f[val]; \
	p++, y++, ptr_g++; \
} 
#define UNLOOP4 UNLOOP UNLOOP UNLOOP UNLOOP
#define UNLOOP8 {UNLOOP4 UNLOOP4}
			for (y = 3; y+8 < bm; )
				UNLOOP8;
			for (; y < bm; )
				UNLOOP;
			*p = '0', p++, *p = '0', p++, *p = '0', p++;
			*p = '\n', p++;
		}
		for (int i = 0; i < 3; i++) {
			memset(p, '0', m), p += m;
			*p = '\n', p++;
		}
		*p = '\0', p++;
		
		printf("Case #%d:\n", ++cases);
		puts(ret);
	}
	return 0;
}

