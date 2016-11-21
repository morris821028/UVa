#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
int n, A[128];

int cmp(const void *x, const void *y) {
	int *a = (int *) x;
	int *b = (int *) y;
	int ca, cb;
	ca = __builtin_popcount(a[1]);
	cb = __builtin_popcount(b[1]);
	if (ca < cb)	return 1;
	if (ca > cb)	return -1;
	ca = a[0], cb = b[0];
	return ca < cb ? -1 : (ca > cb ? 1 : 0);
}

#define FULL ((1<<26)-1)
int ret, suffix[32];
void dfs(int idx, int cost, int fill) {
	if (fill == FULL) {
		if (cost < ret)
			ret = cost;
		return ;
	}
	if (idx == n || cost >= ret || (fill|suffix[idx]) != FULL)
		return ;
	if ((fill&A[idx<<1|1]) != A[idx<<1|1])
		dfs(idx+1, cost+A[idx<<1], fill|A[idx<<1|1]);
	dfs(idx+1, cost, fill);
}
int main() {
	while (scanf("%d", &n) == 1) {
		for (int i = 0; i < n; i++) {
			char s[128];
			int x, mask = 0;
			scanf("%s %d", s, &x);
			for (int j = 0; s[j]; j++)
				mask |= 1<<(s[j]-'a');
			A[i<<1] = x, A[i<<1|1] = mask;
		}
		qsort(A, n, sizeof(int)*2, cmp);

		ret = 0;
		for (int i = 0, mm = 0; i < n; i++)	{
			if ((mm&A[i<<1|1]) != A[i<<1|1])
				mm |= A[i<<1|1], ret += A[i<<1];
			if (mm == FULL)
				break;
		}
		for (int i = n-1, mm = 0; i >= 0; i--) {
			mm |= A[i<<1|1];
			suffix[i] = mm;
		}
		dfs(0, 0, 0);
		printf("%d\n", ret);
	}
	return 0;
}


