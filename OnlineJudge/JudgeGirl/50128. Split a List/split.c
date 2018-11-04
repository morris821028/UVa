#include <stdio.h>
#include "split.h"

#define MAXK 100000
void split(int A[], int *a[], int *head[], int k) {
	static int** tail[MAXK];
	for (int i = 0; i < k; i++)
		tail[i] = NULL;
	
	for (int i = 0; ; i++) {
		int m = A[i]%k;
		if (tail[m] == NULL)
			head[m] = &A[i];
		else
			*(tail[m]) = &A[i];
		tail[m] = &a[i];
		if (a[i] == NULL)
			break;
		a[i] = NULL;
	}
}
