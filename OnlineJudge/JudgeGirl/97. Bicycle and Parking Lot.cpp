#include <stdio.h>
#include <stdlib.h>
#define MAXN 100
int main() {
	int n, m, p, q;
	int x[MAXN], y[MAXN], c[MAXN];
	while (scanf("%d", &n) == 1) {
		int i, j;
		int ret[MAXN] = {};
		for (i = 0; i < n; i++)
			scanf("%d %d %d", &x[i], &y[i], &c[i]);
		scanf("%d", &m);
		for (i = 0; i < m; i++) {
			scanf("%d %d", &p, &q);
			int idx = -1, dist = 0x3f3f3f3f;
			for (j = 0; j < n; j++) {
				if (c[j] == 0)
					continue;
				int d = abs(x[j] - p) + abs(y[j] - q);
				if (d < dist || (d == dist && (x[j] < x[idx] || (x[j] == x[idx] && y[j] < y[idx]))))
					dist = d, idx = j;
			}
			ret[idx]++, c[idx]--;
		}
		for (i = 0; i < n; i++)
			printf("%d\n", ret[i]);
	}
	return 0;
}
