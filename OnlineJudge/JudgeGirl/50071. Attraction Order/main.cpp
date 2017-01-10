#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "attraction.h"

typedef struct {
	unsigned long long idx;
	int x, y;
} V;
static inline int min(int x, int y) {return x < y ? x : y;}
static int cmp(const void *x, const void *y) {
	V *a = (V *) x, *b = (V *) y;
	if (a->idx < b->idx)	return -1;
	return 1;
}
int main(int argc, char *argv[]) {
	assert(argc > 1);
	static Attraction A[MAXM];
	static V T[MAXM];
	int n, m;
	scanf("%d %d", &m, &n);
	{
		FILE *fin = fopen(argv[1], "rb");
		assert(fin != NULL);
		n = fread(A, sizeof(Attraction), MAXM, fin);
		fclose(fin);
	}
	for (int i = 0; i < n; i++) {
		int x = A[i].x, y = A[i].y;
		unsigned long long c = min(min(x, m-1-x), min(y, m-1-y));
		unsigned long long idx = (c) * (8LL*(m-1)-2*c+2)/2;
		if (y == c)
			idx += x-c;
		else if (x == m-1-c)
			idx += y-c + (m-2*c-1);
		else if (y == m-1-c)
			idx += m-c-1-x + 2*(m-2*c-1);
		else
			idx += m-c-1-y + 3*(m-2*c-1);
		T[i].x = x, T[i].y = y, T[i].idx = idx;
	}
	qsort(T, n, sizeof(V), cmp);
	for (int i = 0; i < n; i++)
		printf("%d %d\n", T[i].x, T[i].y);
	return 0;
}

