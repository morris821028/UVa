#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <pthread.h>
#include <inttypes.h>
#include "utils.h"
#include <omp.h>

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
	omp_set_num_threads(4);
	int MM = 4;
	uint32_t hash[4] = {};
	#pragma omp parallel for
	for (int i = 0; i < MM; i++) {
		int l = (i*n)/MM+1;
		int r = ((i+1)*n)/MM;
		uint32_t h = 0;
		for (int j = l; j <= r; j++)
			h = h * SKEY + presum[j];
		hash[i] = h;
	}
	
	uint32_t ret = 0;
	for (int i = 0; i < MM; i++) {
		int l = i * n / MM+1;
		int r = (i+1)*n/ MM;
		ret = ret * fpow(SKEY, r - l+ 1) + hash[i];
	}

	printf("%" PRIu32 "\n", ret);
}

