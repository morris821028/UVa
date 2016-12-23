#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int cmp(const void *a, const void *b) {
	int *x = (int *) a;
	int *y = (int *) b;
	if (*x < *y)	return -1;
	if (*x > *y)	return 1;
	return 0;
}

#define MAXN 32
#define iswap(x, y) {int t = x; x = y, y = t;}
int n, ndiv2, A[MAXN];
char used[MAXN];
int LR[2][MAXN];
struct Node {
	int next, v;
} next[MAXN];
int possible(int u, int lw, int rw, int lidx, int ridx) {
	int ll = lidx+1, rr = ndiv2;
	for (int i = u; i != -1; i = next[i].next) {
		if (rr > ridx)
			rw += rr * next[i].v, rr--;
		else {
			for (int j = next[i].next; j != -1; j = next[j].next) {
				lw += ll * next[j].v, ll++;
			}
			break;
		}
	}
	return lw >= rw;
}
int seesaw(int u, int lw, int rw, int lidx, int ridx, int spos) {
	if (lw == rw && lidx == ndiv2 && ridx == ndiv2) {
		for (int i = ndiv2-1; i >= 0; i--)
			printf("%d ", LR[0][i]);
		printf("_^_");
		for (int i = 0; i < ndiv2; i++)
			printf(" %d", LR[1][i]);
		puts("");
		return 1;
	}

	if (lw > rw) {
		iswap(lw, rw);
		iswap(lidx, ridx);
		spos = !spos;
	}

	if (lidx == ndiv2)
		return 0;
	if (!possible(u, lw, rw, lidx, ridx))
		return 0;
	for (int i = u, prev = INT_MIN, prev_i; i != -1; prev_i = i, i = next[i].next) {
		if (next[i].v == prev)
			continue;
		LR[spos][lidx] = next[i].v;
		if (i != u) {
			next[prev_i].next = next[i].next;
			if (seesaw(u, lw + (lidx+1) * next[i].v, rw, lidx+1, ridx, spos))
				return 1;
			next[prev_i].next = i;
		} else {
			if (seesaw(next[i].next, lw + (lidx+1) * next[i].v, rw, lidx+1, ridx, spos))
				return 1;
		}
		prev = next[i].v;
	}
	return 0;
}
int main() {
	while (scanf("%d", &n) == 1) {
		for (int i = 0; i < n; i++)
			scanf("%d", &A[i]);
		ndiv2 = n/2;
		qsort(A, n, sizeof(int), cmp);
		memset(used, 0, sizeof(used));
		
		for (int i = 0; i < n; i++)
			next[i].next = i+1, next[i].v = A[i];
		next[n-1].next = -1;

		int ret = seesaw(0, 0, 0, 0, 0, 0);

		if (ret == 0)
			puts("N");
	}
	return 0;
}




