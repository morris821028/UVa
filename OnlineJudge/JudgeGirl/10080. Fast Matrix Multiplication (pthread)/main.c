#include <stdio.h>
#include "matrix.h"
#include <pthread.h>
#include <stdlib.h>
#include <string.h>
// #define DEBUG
#define UINT unsigned long 
#define MAXN 2048
#define MAXTHREAD 4
typedef struct SignArg {
	int l, r, N, seed;
	UINT (*A)[MAXN];
	UINT *ret;
} SignArg;

void* thread_gen(void *arg) {
	SignArg *sign = (SignArg *) arg;
	UINT x = sign->seed;
	for (int i = sign->l; i <= sign->r; i++) {
		for (int j = 0; j < sign->N; j++) {
			x = (x * x + sign->seed + i + j)%(sign->N);
			sign->A[i][j] = x;
		}
	}
	free(arg);
}
UINT hash(UINT x) {
	return (x * 2654435761LU);
}
void *thread_hash(void *arg) {
	SignArg *sign = (SignArg *) arg;
	UINT sum = 0;
	UINT h = sign->seed;
	for (int i = sign->l; i <= sign->r; i++) {
		for (int j = 0; j < sign->N; j++) {
			sum += hash(h + sign->A[i][j]);
			h += sign->A[i][j];
		}
	}
	*(sign->ret) = sum;
	free(arg);
}
UINT signature(int N, UINT A[][MAXN]) {
	pthread_t threads[MAXTHREAD];
	UINT sum[MAXTHREAD] = {};

	for (int i = 0; i < MAXTHREAD; i++) {
		SignArg *data = (SignArg *) malloc(sizeof(SignArg));
		data->l = i * N / MAXTHREAD;
		data->r = (i+1) * N / MAXTHREAD - 1;
		data->N = N;
		data->A = A;
		data->seed = i * i;
		data->ret = sum + i;
		pthread_create(&threads[i], NULL, thread_hash, (void *) data);
	}

	for (int i = 0; i < MAXTHREAD; i++)
		pthread_join(threads[i], NULL);
	UINT ret = 0;
	for (int i = 0; i < MAXTHREAD; i++)
		ret += sum[i];
	return ret;
}
static void rand_gen(UINT c, int N, UINT A[][MAXN]) {
	pthread_t threads[MAXTHREAD];

	for (int i = 0; i < MAXTHREAD; i++) {
		SignArg *data = (SignArg *) malloc(sizeof(SignArg));
		data->l = i * N / MAXTHREAD;
		data->r = (i+1) * N / MAXTHREAD - 1;
		data->N = N;
		data->A = A;
		data->seed = c + i * i;
		pthread_create(&threads[i], NULL, thread_gen, (void *) data);
	}
	for (int i = 0; i < MAXTHREAD; i++)
		pthread_join(threads[i], NULL);
/*	UINT x = 2, n = N*N;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			x = (x * x + c + i + j)%n;
			A[i][j] = x;
		}
	}
*/
}


void print_matrix(int N, UINT A[][MAXN]) {
	for (int i = 0; i < N; i++) {
		fprintf(stderr, "[");
		for (int j = 0; j < N; j++)
			fprintf(stderr, " %u", A[i][j]);
		fprintf(stderr, " ]\n");
	}
	printf("====\n");
}
UINT A[MAXN][MAXN], B[MAXN][MAXN], C[MAXN][MAXN];
int main() {
	int N, S1, S2;
	while (scanf("%d %d %d", &N, &S1, &S2) == 3) {
		rand_gen(S1, N, A);
		rand_gen(S2, N, B);
		multiply(N, A, B, C);
#ifdef DEBUG
		print_matrix(N, A);
		print_matrix(N, B);
		print_matrix(N, C);
#endif
		printf("%u\n", signature(N, C));
	}
	return 0;
}
