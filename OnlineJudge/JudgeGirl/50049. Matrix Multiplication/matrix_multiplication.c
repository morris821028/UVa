#include "matrix_multiplication.h"
#include <stdio.h>

#define MAXN 1024
static int **cmp_tmp;

static int cmpInt(int x, int y) {
	if (x == y)	return 0;
	return x < y ? -1 : 1;
}
static int cmp(void *x, void *y) {
	int a = *(int *)x;
	int b = *(int *)y;
	if (cmp_tmp[1][a] != cmp_tmp[1][b])
		return cmpInt(cmp_tmp[1][a], cmp_tmp[1][b]);
	return cmpInt(cmp_tmp[2][a], cmp_tmp[2][b]);
}
static void normalize(int n, int **ptr) {
	static int tmpA[MAXN*MAXN];
	static int buff[MAXN*MAXN];
	for (int i = 0; i < n; i++)
		tmpA[i] = i;
	cmp_tmp = ptr;
	qsort(tmpA, n, sizeof(int), cmp);
	memcpy(buff, ptr[0], sizeof(int)*n);
	for (int i = 0; i < n; i++)
		ptr[0][i] = buff[tmpA[i]];
	memcpy(buff, ptr[1], sizeof(int)*n);
	for (int i = 0; i < n; i++)
		ptr[1][i] = buff[tmpA[i]];
	memcpy(buff, ptr[2], sizeof(int)*n);
	for (int i = 0; i < n; i++)
		ptr[2][i] = buff[tmpA[i]];
}
void matrix_multiplication(int na, int** ptrA, int nb, int** ptrB, int N, int *ret) {
	static int aoff[MAXN];
	int *a_i = ptrA[1], *a_j = ptrA[2], *a_val = ptrA[0];
	int *b_i = ptrB[1], *b_j = ptrB[2], *b_val = ptrB[0];
	int ma = 0;
	normalize(na, ptrA);
	normalize(nb, ptrB);
	for (int i = 0, p = -1; i < na; i++) {
		if (a_i[i] != p)
			aoff[ma++] = i, p = a_i[i];
	}
	aoff[ma] = na;
	
	memset(ret, 0, sizeof(int)*N*N);
	for (int i = 0; i < ma; i++) {
		int idx1 = aoff[i], top1 = aoff[i+1];
		int C[MAXN] = {};
		for (int idx2 = 0; idx2 < nb && idx1 < top1; ) {
			if (a_j[idx1] == b_i[idx2]) {
				C[b_j[idx2]] += a_val[idx1] * b_val[idx2];
				idx2++;
			}
			if (idx2 < nb && a_j[idx1] != b_i[idx2]) {
				if (a_j[idx1] < b_i[idx2])
					idx1++;
				else
					idx2++;
			}
		}
		
		int offset = a_i[aoff[i]]*N;
		for (int j = 0; j < N; j++) {
			ret[offset+j] = C[j];
		}
	}
}



