#include <stdio.h>
#define MAXN 128
#define MAXM 128

int minCost(int A[], int n) {
	int sum = 0;
	int pos = 0, cost = 0, mn;
	for (int i = 0; i < n; i++)
		sum += A[i], cost += A[i] * i;
	mn = cost;
	for (int i = 1, prev = 0; i < n; i++) {
		prev += A[i-1];
		cost = cost + prev - (sum - prev);
		if (cost < mn)
			mn = cost, pos = i;
	}
	return pos;
}
int main() {
	int n, m, x;
	while (scanf("%d %d", &n, &m) == 2) {
		int X[MAXN] = {}, Y[MAXM] = {};
		for (int i = 0; i < n; i++)
			for (int j = 0; j < m; j++)
				scanf("%d", &x), X[i] += x, Y[j] += x;
		int rx = minCost(X, n);
		int ry = minCost(Y, m);
		printf("%d %d\n", rx + 1, ry + 1);
	}
	return 0;
}
