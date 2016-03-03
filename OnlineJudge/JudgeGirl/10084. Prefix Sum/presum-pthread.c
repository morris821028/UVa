#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <pthread.h>
#include "utils.h"

typedef struct Argu {
    int l, r;
    uint32_t *psum;
	uint32_t key;
} Argu;
int min(int x, int y) {
	return x < y ? x : y;
}
void* subtask1(void *argu) {
	Argu data = *((Argu *) argu);
	int l = data.l, r = data.r;
	uint32_t *psum = data.psum; 
	uint32_t sum = 0, key = data.key;
	for (int i = l, j = 0; i <= r; i++, j++) {
		sum += encrypt(i, key);
		psum[j] = sum;
	}
	free(argu);
}
void* subtask2(void *argu) {
	Argu data = *((Argu *) argu);
	int l = data.l, r = data.r;
	uint32_t *psum = data.psum; 
	uint32_t base = data.key;
	for (int i = l, j = 0; i <= r; i++, j++)
		psum[j] += base;
	free(argu);
}
#define MAXN 10000005
#define MAX_THREAD 4
uint32_t prefix_sum[MAXN];
int main() {
	int n;
	uint32_t key;
	while (scanf("%d %" PRIu32, &n, &key) == 2) {
		int BLOCK = (n+MAX_THREAD-1) / MAX_THREAD, m = 0;
		pthread_t threads[MAX_THREAD];
		for (int i = 1; i <= n; ) {
			Argu *argu = (Argu *) malloc(sizeof(Argu));
			argu->l = i, argu->r = min(n, i + BLOCK - 1);
			argu->psum = prefix_sum + i, argu->key = key;
			i += BLOCK;
			pthread_create(&threads[m], NULL, subtask1, argu), m++;
		}
		for (int i = 0; i < m; i++)
			pthread_join(threads[i], NULL);
		
		m = 0;
		uint32_t block_sum = 0;
		for (int i = 1; i <= n; i) {
			uint32_t tmp = block_sum;
			block_sum += prefix_sum[min(n, i+BLOCK-1)];
			Argu *argu = (Argu *) malloc(sizeof(Argu));
			argu->l = i, argu->r = min(n, i + BLOCK - 1);
			argu->psum = prefix_sum + i, argu->key = tmp;
			i += BLOCK;
			pthread_create(&threads[m], NULL, subtask2, argu), m++;
		}
		for (int i = 0; i < m; i++)
			pthread_join(threads[i], NULL);
		output(prefix_sum, n);
	}
	return 0;
}
