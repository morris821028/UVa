#include "subset.h"
#include <stdlib.h>
#include <stdio.h>

static int dfs(int A[], int B[], int suf[], int n, int K, int S) {
	if (S == 0 && K == 0)
		return 1;
	if (K < 0 || S < 0 || n == 0 || K > suf[0])
		return 0;
	for (int i = B[0]; i >= 0; i--) {
		if (dfs(A+1, B+1, suf+1, n-1, K-i*A[0], S-i))
			return 1;
	}
	return 0;
}
static int cmp(const void *a, const void *b) {
	return *(int *) b - *(int *) a;
}
int subset(int A[], int n, int K, int S) {
	qsort(A, n, sizeof(int), cmp);
	static int suffix[128], tA[128], tB[128];
	int m = 1;
	tA[0] = A[0], tB[0] = 1;
	for (int i = 1; i < n; i++) {
		if (A[i] == A[i-1])
			tB[m-1]++;
		else
			tA[m] = A[i], tB[m] = 1, m++;
	}
	int sum = 0;
	for (int i = m-1; i >= 0; i--)
		sum += tA[i]*tB[i], suffix[i] = sum;
	return dfs(tA, tB, suffix, n, K, S);
}
