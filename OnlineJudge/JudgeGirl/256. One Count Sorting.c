#include <stdio.h>
#include <stdlib.h>

int n = 0;
long long A[1024];
int cmp(const void *x, const void *y) {
	if (__builtin_popcountll(*(long long*) x)
		!= __builtin_popcountll(*(long long*) y))
	return __builtin_popcountll(*(long long*) x)
		- __builtin_popcountll(*(long long*) y);
	long long a = *(long long*) x;
	long long b = *(long long*) y;
	if (a < b)	return -1;
	if (a > b)	return 1;
	return 0;
}
int main() {
	while (scanf("%lld", &A[n]) == 1)
		n++;
	qsort(A, n, sizeof(long long), cmp);
	for (int i = 0; i < n; i++)
		printf("%lld\n", A[i]);
	return 0;
}
