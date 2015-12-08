#include <stdio.h>
#include "subset.h"

int main() {
	int n, K, S;
	while (scanf("%d %d %d", &n, &K, &S) == 3) {
		int A[128];
		for (int i = 0; i < n; i++)
			scanf("%d", &A[i]);
		printf("%d\n", subset(A, n, K, S));
	}
	return 0;
}
