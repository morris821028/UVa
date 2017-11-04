#include "constructTable.h"
#include <stdlib.h>
#include <string.h>

int ***constructTable(int A[], int B[]) {
	int n = 0;
	while (A[n])
		n++;
	int ***ret = (int ***) malloc(sizeof(int**)*(n+1));
	for (int i = 0, bpos = 0; i < n; i++) {
		ret[i] = (int **) malloc(sizeof(int*)*(A[i]+1));
		for (int j = 0; j < A[i]; j++) {
			ret[i][j] = &B[bpos];
			while (B[bpos++] != 0);
		}
		ret[i][A[i]] = NULL;
	}
	return ret;
}
