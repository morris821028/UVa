#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

static inline uint32_t rotate_left(uint32_t x, uint32_t n) {
	return  (x << n) | (x >> (32-n));
}
static inline uint32_t encrypt(uint32_t m, uint32_t key) {
	return (rotate_left(m, key&31) + key)^key;
}

#define MAXN 1048576
#define MAXL 1048576
typedef struct ELE {
	int i, j;
	uint32_t v;
} ELE;
ELE LA[MAXL], LB[MAXL];

void SpMV(int N, int M, int R, ELE LA[], int na, ELE LB[], int nb) {
	int ma = 0;
	static int aoff[MAXN];
	for (int i = 0, p = -1; i < na; i++) {
		if (LA[i].i != p)
			aoff[ma++] = i, p = LA[i].i;
	}
	aoff[ma] = na;
	
	uint32_t hash = 0;
	int chunk = 8;
    #pragma omp parallel for schedule(dynamic, chunk) reduction(+: hash)
	for (int i = 0; i < ma; i++) {
		int idx1 = aoff[i], top1 = aoff[i+1];
		int r = LA[idx1].i;
		uint32_t *C = (uint32_t *) calloc(R, sizeof(uint32_t));
		for (int idx2 = 0; idx2 < nb && idx1 < top1; ) {
			if (LA[idx1].j == LB[idx2].i) {
				C[LB[idx2].j] += LA[idx1].v * LB[idx2].v;
				idx2++;
			}
			if (idx2 < nb && LA[idx1].j != LB[idx2].i) {
				if (LA[idx1].j < LB[idx2].i)
					idx1++;
				else
					idx2++;
			}
		}
		for (int j = 0; j < R; j++) {
			if (C[j])
				hash += encrypt((r+1)*(j+1), C[j]);
		}
		free(C);
	}
	
	printf("%u\n", hash);
}
int main() {
	uint32_t N, M, R, nA, nB;
	while (scanf("%d %d %d", &N, &M, &R) == 3) {
		scanf("%d %d", &nA, &nB);
		for (int i = 0; i < nA; i++)
			scanf("%d %d %d", &LA[i].i, &LA[i].j, &LA[i].v);
		for (int i = 0; i < nB; i++)
			scanf("%d %d %d", &LB[i].i, &LB[i].j, &LB[i].v);
		SpMV(N, M, R, LA, nA, LB, nB);
	}
	return 0;
}
