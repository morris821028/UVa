#include <stdio.h>
#include "fill_array.h"
int main() {
	int arr[100] = {};
	int *ptr[100];
	int n = 6, m = 0;
	int A[100] = {0, 5, 6, 9, 3, 12};
	for (int i = 0; i < n; i++) {
		ptr[i] = &arr[A[i]];
		if (A[i] > m)	m = A[i];
	}
	fill_array(ptr, n);
	for (int i = 0; i <= m; i++)
		printf("%d%c", arr[i], " \n"[i==m]);
	return 0;
}
