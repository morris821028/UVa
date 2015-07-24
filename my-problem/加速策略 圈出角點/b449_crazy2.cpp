#include <bits/stdc++.h>
#pragma GCC optimize ("O3")
using namespace std;

//const int dx[] = {-3, -3, -2, -1, 0, 1, 2, 3, 3, 3, 2, 1, 0, -1, -2, -3};
//const int dy[] = {0, 1, 2, 3, 3, 3, 2, 1, 0, -1, -2, -3, -3, -3, -2, -1};
const int MAXH = 2048, MAXW = 2048;
const int MAXN = MAXH * MAXW;
char g[MAXH][MAXW], ret[MAXH*MAXW];
int n, m;
#define dx_00 -3
#define dx_01 -3
#define dx_02 -2
#define dx_03 -1
#define dx_40 0
#define dx_41 1
#define dx_42 2
#define dx_43 3
#define dx_80 3
#define dx_81 3
#define dx_82 2
#define dx_83 1
#define dx_120 0
#define dx_121 -1
#define dx_122 -2
#define dx_123 -3
#define dy_00 0
#define dy_01 1
#define dy_02 2
#define dy_03 3
#define dy_40 3
#define dy_41 3
#define dy_42 2
#define dy_43 1
#define dy_80 0
#define dy_81 -1
#define dy_82 -2
#define dy_83 -3
#define dy_120 -3
#define dy_121 -3
#define dy_122 -2
#define dy_123 -1
#define T(x, y, z, w) ((g[x + dx_##z##w][y + dy_##z##w])<<(z+w)) 
#define UNLOOPX(i) (val&cor[i]) == 0 || (val&cor[i]) == cor[i] || \
(val&cor[i+1]) == 0 || (val&cor[i+1]) == cor[i+1] || \
(val&cor[i+2]) == 0 || (val&cor[i+2]) == cor[i+2] || \
(val&cor[i+3]) == 0 || (val&cor[i+3]) == cor[i+3]
#define UNLOOPXALL UNLOOPX(0) || UNLOOPX(4) || UNLOOPX(8) || UNLOOPX(12)
#define UNLOOPY(i) T(x, y, i, 0) | T(x, y, i, 1) | T(x, y, i, 2) | T(x, y, i, 3) 
#define UNLOOPYALL UNLOOPY(0) | UNLOOPY(4) | UNLOOPY(8) | UNLOOPY(12)
typedef unsigned short int UINT16;
UINT16 cor[16] = {};
UINT16 rotate_left(UINT16 x, UINT16 n) {
	return  (x << n) | (x >> (16-n));
}
int f[1<<16];
int main() {
	UINT16 val;
	for (int i = 0, j = (1<<12)-1; i < 16; i++, j = rotate_left(j, 1))
		cor[i] = j;
	for (int i = 0; i < 1<<16; i++) {
		val = i;
		f[i] = UNLOOPXALL;
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
		for (int x = 3; x < bn; x++) {
			*p = '0', p++, *p = '0', p++, *p = '0', p++;
#define UNLOOP { \
	val = UNLOOPYALL; \
	*p = f[val] | '0'; \
	p++, y++; \
} 
#define UNLOOP4 UNLOOP UNLOOP UNLOOP UNLOOP
#define UNLOOP8 {UNLOOP4 UNLOOP4}
			int y = 3;
			for (; y+8 < bm; )
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

