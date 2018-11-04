#include "constructPointerArray.h"

void constructPointerArray(const int a[1024][1024], const int *b[1024][1024], int n) {
	static int pos[MAXN*MAXN];
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			pos[a[i][j]] = (i<<12)|j;
	
	for (int i = 0; i < n*n; i++) {
		int p = i%n, q = i/n;
		int v = a[p][q] + 1;
		if (v >= n*n)
			v = 0;
		int x = pos[v]>>12, y = pos[v]&((1<<12)-1);
		b[p][q] = &a[x][y];
	}
}
