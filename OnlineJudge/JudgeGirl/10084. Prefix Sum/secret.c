#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <pthread.h>
#include <inttypes.h>
#include <pthread.h>
#include "utils.h"

typedef struct Argu {
	int l, r;
	uint32_t *psum;
	uint32_t key;
} Argu;
static int min(int x, int y) {
	return x < y ? x : y;
}
#define SKEY 10007
static void* subtask_hash(void *argu) {
	Argu *data = (Argu *) argu;
	int l = data->l, r = data->r;
	uint32_t *psum = data->psum;
	uint32_t hash = 0;
	for (int i = l, j = 0; i <= r; i++, j++)
		hash = hash * SKEY + psum[j];
	data->key = hash;
}
#define MAXN 10000005
#define MAX_THREAD 4
static uint32_t fpow(uint32_t a, uint32_t b) {
	uint32_t ret = 1;
	while (b) {
		if (b&1)
			ret = ret * a;
		b >>= 1, a = a * a;
	}
	return ret;
}
void output(uint32_t presum[], int n) {
	int BLOCK = (n + MAX_THREAD-1) / MAX_THREAD, m = 0;
	pthread_t threads[MAX_THREAD];
	Argu A[MAX_THREAD];
	for (int i = 1; i <= n; ) {
		Argu *argu = A+m;
		argu->l = i, argu->r = min(n, i + BLOCK - 1);
		argu->psum = presum + i;
		i += BLOCK;
		pthread_create(&threads[m], NULL, subtask_hash, argu), m++;
	}

	for (int i = 0; i < m; i++)
		pthread_join(threads[i], NULL);
	
	uint32_t ret = 0;
	for (int i = 0; i < m; i++) 
		ret = ret * fpow(SKEY, A[i].r - A[i].l + 1) + A[i].key;

	printf("%" PRIu32 "\n", ret);
}

