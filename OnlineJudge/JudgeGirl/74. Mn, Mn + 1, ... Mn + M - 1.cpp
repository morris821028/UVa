#include <stdio.h>
#include <stdlib.h>

int A[500000] = {}, R[500000] = {};
int main() {
	int n, m;
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
		scanf("%d", &A[i]);
	scanf("%d", &m);
	for (int i = 0; i < n; i++)
		R[abs(A[i]%m)]++;
	for (int i = 0; i < m; i++)
		printf("%d\n", R[i]);
	return 0;
}

