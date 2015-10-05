#include "snake.h"
#include <stdlib.h>
int cmp(const void *s1, const void *s2) {
    return **(int **)s1 - **(int **)s2;
}
void snake(const int *ptr_array[100][100], int m) {
	int *A[10000], n = 0;
	for (int i = 0; i < m; i++)
		for (int j = 0; j < m; j++)
			A[n++] = ptr_array[i][j];
	qsort(A, n, sizeof(int*), cmp);
	n = 0;
	for (int i = 0; i < m; i++) {
		int dir = i%2 ? -1 : 1;
		for (int j = i%2 ? m-1 : 0; j >= 0 && j < m; j += dir)
			ptr_array[i][j] = A[n++];
	}
}
