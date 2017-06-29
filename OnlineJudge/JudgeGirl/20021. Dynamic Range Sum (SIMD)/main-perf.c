#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <assert.h>
#include "DRS.h"

static uint32_t seed = 0;
static void p_srand(uint32_t x) { seed = x;}
static uint32_t p_rand() {return seed = (seed*9301 + 49297);}

static void swap(int *x, int *y) {
	int tmp = *x;
	*x = *y;
	*y = tmp;
}
static inline Rect rand_rect(int R) {
	Rect r;
	r.lx = p_rand()%R;
	r.ly = p_rand()%R;
	r.rx = p_rand()%R;
	r.ry = p_rand()%R;
	if (r.lx > r.rx)	swap(&r.lx, &r.rx);
	if (r.ly > r.ry)	swap(&r.ly, &r.ry);
	return r;
}

static void init(int N, int R, int32_t x[], int32_t y[], int32_t w[]) {
	for (int i = 0; i < N; i++) {
		x[i] = p_rand()%R;
		y[i] = p_rand()%R;
		w[i] = p_rand()%R;
	}
}

static void tick(int N, int R, int32_t x[], int32_t y[], int32_t w[]) {
	for (int i = 0; i < 5; i++)	{
		int idx = p_rand()%N;
		x[idx] = p_rand()%R;
		y[idx] = p_rand()%R;
	}
	for (int i = 0; i < 5; i++)	{
		int idx = p_rand()%N;
		w[idx] = p_rand()%R;
	}
}

#define MAXN 1048576
int main() {
	static int32_t x[MAXN], y[MAXN], w[MAXN];
	int N = 1000, M = 10000, R = 100, S;
	assert(scanf("%d %d %d %d", &N, &M, &R, &S) == 4);
	p_srand(S);
	init(N, R, x, y, w);

	int32_t hash = 0;
	for (int it = 0; it < M; it++) {
		Rect rect = rand_rect(R);
		int32_t ret = search_range(rect, x, y, w, N);
		hash ^= ret;
		tick(N, R, x, y, w);
	}
	printf("%" PRIi32 "\n", hash);
	return 0;
}
