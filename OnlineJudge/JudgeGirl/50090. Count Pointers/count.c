#include "count.h"
#include <stdlib.h>
#include <stdio.h>
#define MAXN 512

static int cmp_addr(const void *x, const void *y) {
	int *a = *(int **) x, *b = *(int **) y;
	if (a < b) return -1;
	if (a == b)	return 0;
	return 1;
}
static int cmp_ret(const void *x, const void *y) {
	int *a = (int *) x, *b = (int *) y;
	if (a[1] != b[1])
		return a[1] < b[1] ? -1 : 1;
	return a[0] < b[0] ? -1 : 1;
}
void count(int **p[]) {
	int *A[MAXN], n = 0;
	for (; p[0]; p++) 
		A[n] = *p[0], n++;
	qsort(A, n, sizeof(int*), cmp_addr);
	int B[MAXN][2], m = 0;
	for (int i = 0; i < n; ) {
		int cnt = 0, j = i;
		while (j < n && A[i] == A[j])
			j++, cnt++;
		B[m][0] = *A[i], B[m][1] = cnt, m++;
		i = j;
	}
	qsort(B, m, sizeof(int)*2, cmp_ret);
	for (int i = 0; i < m; i++)
		printf("%d %d\n", B[i][0], B[i][1]);
}
