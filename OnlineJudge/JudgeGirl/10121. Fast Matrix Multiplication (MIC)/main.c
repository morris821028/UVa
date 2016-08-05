#include <stdio.h>
#include "matrix.h"

// #define DEBUG
#define UINT unsigned long 
#define MAXN 2048
void rand_gen(UINT c, int N, UINT A[][MAXN]) {
	UINT x = 2, n = N*N;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			x = (x * x + c + i + j)%n;
			A[i][j] = x;
		}
	}
}
void print_matrix(int N, UINT A[][MAXN]) {
	for (int i = 0; i < N; i++) {
		fprintf(stderr, "[");
		for (int j = 0; j < N; j++)
			fprintf(stderr, " %u", A[i][j]);
		fprintf(stderr, " ]\n");
	}
}
UINT hash(UINT x) {
	return (x * 2654435761LU);
}
UINT signature(int N, UINT A[][MAXN]) {
	UINT h = 0;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++)
			h = hash(h + A[i][j]);
	}
	return h;
}
static UINT A[MAXN][MAXN], B[MAXN][MAXN], C[MAXN][MAXN];
int main() {
	int N, S1, S2;
	while (scanf("%d %d %d", &N, &S1, &S2) == 3) {
		rand_gen(S1, N, A);
		rand_gen(S2, N, B);
		#pragma offload target(mic) in(A,B) out(C)
		{
			multiply(N, A, B, C);
		}
#ifdef DEBUG
		print_matrix(N, A);
		print_matrix(N, B);
		print_matrix(N, C);
#endif
		printf("%u\n", signature(N, C));
	}
	return 0;
}
