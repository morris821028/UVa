#include <stdio.h>

void merge(int a[], int b[], int* next_a[], int* next_b[]) {
	int p = 0, q = 0;
	int **prev = NULL;
	while (1) {
		if (a[p] < b[q]) {
			if (prev != NULL)
				*prev = &a[p];
			prev = &next_a[p], p++;
			if (*prev == NULL) {
				*prev = &b[q];
				break;
			}
		} else {
			if (prev != NULL)
				*prev = &b[q];
			prev = &next_b[q], q++;
			if (*prev == NULL) {
				*prev = &a[p];
				break;
			}
		}
	}
}
