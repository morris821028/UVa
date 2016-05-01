#include <bits/stdc++.h>
using namespace std;

int A[131072][10];
int main() {
	int n, m, x;
	while (scanf("%d", &n) == 1) {
		for (int i = 1; i <= n; i++) {
			scanf("%d", &x);
			for (int j = 0; j < 10; j++)
				A[i][j] = A[i-1][j];
			A[i][x]++;
		}
		scanf("%d", &m);
		for (int i = 0; i < m; i++) {
			int l, r, ret = 0;
			scanf("%d %d", &l, &r);
			for (int j = 0; j < 10; j++)
				ret += A[r][j] - A[l-1][j] > 0;
			printf("%d\n", ret);
		}
	}
	return 0;
}

