#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <omp.h>
#define MAXQ (1<<16)
#define MAXN 32
static int y_valid[32] = {};
int mask;
int dfs(int lv, int row, int dia1, int dia2) {
    int pos = mask & (~(row | dia1 | dia2)) & y_valid[lv];
    int ret = 0;
    while (pos) {
	    int p = pos & (-pos);
	    pos ^= p;
	    if ((row|p) != mask)
		    ret += dfs(lv+1, row|p, (dia1|p)<<1, (dia2|p)>>1);
	    else
		    ret++;
    }
    return ret;
}
static inline int min(int x, int y) {return x < y ? x : y;}

int test(int p0, int p1, int p2, int n) {
	int arr[] = {p0, p1, p2};
	int row = 0, dia1 = 0, dia2 = 0;
	for (int lv = 0; lv < sizeof(arr)/sizeof(arr[0]); lv++) {
		int pos = mask & (~(row | dia1 | dia2)) & y_valid[lv];
		int p = 1<<arr[lv];
		if (pos&p)
			row |= p, dia1 = (dia1|p)<<1, dia2 = (dia2|p)>>1;
		else
			return 0;
	}
	return dfs(sizeof(arr)/sizeof(arr[0]), row, dia1, dia2);
}
int totalNQueens(int n) {
	int ret = 0;
	mask = (1<<n)-1;
	#pragma omp parallel
	{
		#pragma omp for schedule(dynamic) collapse(3) reduction(+: ret)
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				for (int k = 0; k < n; k++) {
					ret += test(i, j, k, n);
				}
			}
		}
	}
	return ret;
}
int main() {
	int cases = 0, n;
	char s[32] = {};
	while (scanf("%d", &n) == 1 && n) {
		for (int i = 0; i < n; i++) {
			scanf("%s", s);
			y_valid[i] = (1<<n)-1;
			for (int j = 0; j < n; j++) {
				if (s[j] == '*')
					y_valid[i] ^= (1<<j);
			}
		}
		int ret = totalNQueens(n);
		printf("Case %d: %d\n", ++cases, ret);
	}
	return 0;
}
