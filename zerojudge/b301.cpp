#include <stdio.h>
int parent[32767], weight[32767];
int findp(int x) {
	return parent[x] == x ? x : parent[x] = findp(parent[x]);
}
int joint(int x, int y) {
	x = findp(x), y = findp(y);
	if (x == y)	return 0;
	if (weight[x] > weight[y])
		weight[x] += weight[y], parent[y] = x;
	else
		weight[y] += weight[x], parent[x] = y;
	return 1;
} 
int main() {
	int n, q, a, b, x, y;
	int ex[32767], ey[32767];
	while (scanf("%d %d", &n, &q) == 2) {
		for (int i = 0; i < n; i++)
			scanf("%d %d", &ex[i], &ey[i]);
		for (int i = 0; i < q; i++) {
			scanf("%d %d %d %d", &a, &b, &x, &y);
			for (int j = 0; j <= n; j++)
				parent[j] = j, weight[j] = 1;
			int ok = 0;
			for (int j = 0; j < n; j++) {
				if (ex[j] == x && ey[j] == y)
					continue;
				if (ex[j] == y && ey[j] == x)
					continue;
				joint(ex[j], ey[j]);
				if (findp(a) == findp(b)) {
					ok = 1;
					break;
				}
			}
			puts(ok ? "STOP" : "GO");
		}
	}
	return 0;
}
