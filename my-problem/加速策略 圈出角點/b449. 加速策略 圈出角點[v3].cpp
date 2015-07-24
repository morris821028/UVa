#include <bits/stdc++.h>
using namespace std;

const int dx[] = {-3, -3, -2, -1, 0, 1, 2, 3, 3, 3, 2, 1, 0, -1, -2, -3};
const int dy[] = {0, 1, 2, 3, 3, 3, 2, 1, 0, -1, -2, -3, -3, -3, -2, -1};
const int MAXH = 2048, MAXW = 2048;
const int MAXN = MAXH * MAXW;
char g[MAXH][MAXW], ret[MAXH*MAXW];
int n, m;
#define T(x, y, z) ((g[x+dx[z]][y+dy[z]])<<z)
#define UNLOOPX(i) (val&corner[i]) == 0 || (val&corner[i]) == corner[i] || \
(val&corner[i+1]) == 0 || (val&corner[i+1]) == corner[i+1] || \
(val&corner[i+2]) == 0 || (val&corner[i+2]) == corner[i+2] || \
(val&corner[i+3]) == 0 || (val&corner[i+3]) == corner[i+3]
#define UNLOOPXALL UNLOOPX(0) || UNLOOPX(4) || UNLOOPX(8) || UNLOOPX(12)
#define UNLOOPY(i)  T(x, y, i) | T(x, y, i+1) | T(x, y, i+2) | T(x, y, i+3) 
#define UNLOOPYALL UNLOOPY(0) | UNLOOPY(4) | UNLOOPY(8) | UNLOOPY(12)
typedef unsigned short int UINT16;
UINT16 corner[16] = {};
UINT16 rotate_left(UINT16 x, UINT16 n) {
	return  (x << n) | (x >> (16-n));
}
int main() {
	for (int i = 0, j = (1<<12)-1; i < 16; i++, j = rotate_left(j, 1))
		corner[i] = j;
		
	int cases = 0;
	while (scanf("%d %d", &n, &m) == 2) {
		while (getchar() != '\n');
		for (int i = 0; i < n; i++) {
			fgets(g[i], MAXW, stdin);
			for (int j = 0; j < m; j++)
				g[i][j] -= '0';
		}
		int bn = n-3, bm = m-3;
		char *p = ret;
		UINT16 val;
		for (int i = 0; i < 3; i++) {
			memset(p, '0', m), p += m;
			*p = '\n', p++;
		}
		for (int x = 3; x < bn; x++) {
			*p = '0', p++;
			*p = '0', p++;
			*p = '0', p++;
			for (int y = 3; y < bm; y++) {
				val = UNLOOPYALL;
				*p = (UNLOOPXALL) + '0', p++;
			}
			*p = '0', p++;
			*p = '0', p++;
			*p = '0', p++;
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

