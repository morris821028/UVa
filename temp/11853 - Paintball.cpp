#include <stdio.h>
#include <math.h>
#include <string.h>
#include <algorithm>
using namespace std;

#define MAXN 1024
#define W 1000
#define H 1000
struct Circle {
	double x, y, r;
} C[MAXN];
int visited[MAXN], N;
int intersection(Circle a, Circle b) {
	double x = a.x - b.x, y = a.y - b.y, r = a.r + b.r;
	return x * x + y * y <= r * r;
}
int dfs(int u, double &lSt, double &rEd) {
	visited[u] = 1;
	if (C[u].y - C[u].r <= 0)
		return 1; // top-to-bottom
	if (C[u].x - C[u].r <= 0)
		lSt = min(lSt, C[u].y - sqrt(pow(C[u].r, 2) - pow(C[u].x, 2)));
	if (C[u].x + C[u].r >= W)
		rEd = min(rEd, C[u].y - sqrt(pow(C[u].r, 2) - pow(W - C[u].x, 2)));
	for (int v = 1; v <= N; v++) {
		if (visited[v])	continue;
		if (intersection(C[u], C[v])) {
			if (dfs(v, lSt, rEd))	
				return 1;
		}
	}
	return 0;
}
int main() {
	
	while (scanf("%d", &N) == 1) {
		for (int i = 0; i < N; i++)
			scanf("%lf %lf %lf", &C[i].x, &C[i].y, &C[i].r);
		double lSt = 1000, rEd = 1000;
		int ok = 1;
		memset(visited, 0, sizeof(visited));
		for (int i = 0; i < N; i++) {
			if (visited[i] == 0 && C[i].y + C[i].r >= H) {
				if (dfs(i, lSt, rEd)) {
					ok = 0;
					break;
				}
			}
		}
		if (ok)
			printf("%.2lf %.2lf %.2lf %.2lf\n", (double) 0, lSt, (double) W, rEd);
		else
			puts("IMPOSSIBLE");
	}
	return 0;
}
