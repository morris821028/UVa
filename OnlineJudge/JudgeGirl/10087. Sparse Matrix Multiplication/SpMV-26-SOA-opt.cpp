#include <bits/stdc++.h>
using namespace std;

static inline uint32_t rotate_left(uint32_t x, uint32_t n) {
	return  (x << n) | (x >> (32-n));
}
static inline uint32_t encrypt(uint32_t m, uint32_t key) {
	return (rotate_left(m, key&31) + key)^key;
}

#define MAXN 1048576
#define MAXL 1048576
typedef struct ELE {
	int i[MAXL], j[MAXL];
	uint32_t v[MAXL];
} ELE;
ELE LA, LB;

void SpMV(int N, int M, int R, ELE &LA, int na, ELE &LB, int nb) {
	int ma = 0;
	static int aoff[MAXN];
	static int boff[MAXN];
	#pragma omp parallel sections
	{
		#pragma omp section
		{
			for (int i = 0, p = -1; i < na; i++) {
				if (LA.i[i] != p)
					aoff[ma++] = i, p = LA.i[i];
			}
			aoff[ma] = na;
		}
		#pragma omp section
		{
			memset(boff, -1, sizeof(boff));
			for (int i = 0, p = -1; i < nb; i++) {
				if (LB.i[i] != p)
					boff[LB.i[i]] = i, p = LB.i[i];
			}
			boff[M] = nb;
			for (int i = M-1; i >= 0; i--) {
				if (boff[i] == -1)
					boff[i] = boff[i+1];
			}
		}
	}
	
	uint32_t hash = 0;
	int chunk = 16;
    #pragma omp parallel for schedule(dynamic, chunk) reduction(+: hash)
	for (int i = 0; i < ma; i++) {
		int idx1 = aoff[i], top1 = aoff[i+1];
		int r = LA.i[idx1];
		uint32_t *C = (uint32_t *) calloc(R, sizeof(uint32_t));
		for (; idx1 < top1; ) {
			int L = boff[LA.j[idx1]], R = boff[LA.j[idx1]+1];
			int v = LA.v[idx1];
			for (int idx2 = L; idx2 < R; idx2++)
				C[LB.j[idx2]] += v * LB.v[idx2];
			idx1++;
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
			scanf("%d %d %d", &LA.i[i], &LA.j[i], &LA.v[i]);
		for (int i = 0; i < nB; i++)
			scanf("%d %d %d", &LB.i[i], &LB.j[i], &LB.v[i]);
		SpMV(N, M, R, LA, nA, LB, nB);
	}
	return 0;
}
