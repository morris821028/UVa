#include <stdio.h>
#include <stdlib.h>
int cmp(const void *i, const void *j) {
	return *(int *)i - *(int *)j;
}
int main() {
	int T, n, i, A[501];
	scanf("%d", &T);
	while(T--) {
		scanf("%d", &n);
		for(i = 0; i < n; i++)
			scanf("%d", &A[i]);
		qsort(A, n, sizeof(int), cmp);
		int min = 0, select = n/2;
		for(i = 0; i < n; i++)
			min += abs(A[select] - A[i]);
		printf("%d\n", min);
	}
    return 0;
}
