#include <bits/stdc++.h> 
using namespace std;

int main() {
	int N, M, Q;
	int x, y, cmd;
	int g[105][105] = {}, en[105] = {};
	scanf("%d %d", &N, &M);
	for (int i = 0; i < M; i++) {
		scanf("%d %d", &x, &y);
		if (g[x][y])
			continue;
		g[x][y] = g[y][x] = 1;
		en[x]++, en[y]++;
	}
	scanf("%d", &Q);
	for (int i = 0; i < Q; i++) {
		scanf("%d", &cmd);
		if (cmd == 1) {
			scanf("%d", &x);
			printf("%d\n", en[x]);
		} else {
			scanf("%d %d", &x, &y);
			puts(g[x][y] ? "Yes" : "No");
		}
	}
	return 0;
}
