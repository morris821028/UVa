#include <stdio.h> 
#include <vector>
#include <queue> 
#include <algorithm>
#include <sstream>
using namespace std;
struct edge {
	int to, v, label;
	edge(int a=0, int b=0, int c=0):
		to(a), v(b), label(c){}
};
vector<edge> g[128];
int mxfloor[128], mnfloor[128], T[128];
int dist[128], inq[128];
void spfa(int N, int K) {
	for (int i = 0; i < 128; i++)
		dist[i] = 0x3f3f3f3f;
	int u, v, w, l;
	queue<int> Q;
	Q.push(0), dist[0] = 0;
	while (!Q.empty()) {
		u = Q.front(), Q.pop();
		inq[u] = 0;
		for (int i = 0; i < g[u].size(); i++) {
			v = g[u][i].to, l = g[u][i].label;
			w = g[u][i].v + T[l] * max(mxfloor[l] - u, u - mnfloor[l]) + 5;
			if (dist[v] > dist[u] + w) {
				dist[v] = dist[u] + w;
				if (!inq[v]) {
					inq[v] = 1;
					Q.push(v);
				}
			}
		}
	}
	if (dist[K] == 0x3f3f3f3f)
		puts("IMPOSSIBLE");
	else
		printf("%d\n", K == 0 ? 0 : (dist[K] - 5));
}
int main() {
	int N, K, f[128];
	char s[1024];
	while (scanf("%d %d", &N, &K) == 2) {
		for (int i = 0; i < N; i++)
			scanf("%d", &T[i]);
		for (int i = 0; i < 128; i++)
			g[i].clear();
		while (getchar() != '\n');
		for (int i = 0; i < N; i++) {
			gets(s);
			stringstream sin(s);
			int n = 0;
			while (sin >> f[n])
				n++;
			mxfloor[i] = -1, mnfloor[i] = 0x3f3f3f3f;
			for (int j = 0; j < n; j++) {
				mxfloor[i] = max(mxfloor[i], f[j]);
				mnfloor[i] = min(mnfloor[i], f[j]);
				for (int k = 0; k < n; k++) {
					if (j == k)	continue;
					g[f[j]].push_back(edge(f[k], abs(f[k] - f[j]) * T[i], i));
				}
			}
		}
		spfa(N, K);
	}
	return 0;
}
/*
2 30
10 5
0 1 3 5 7 9 11 13 15 20 99
4 13 15 19 20 25 30
2 30
10 1
0 5 10 12 14 20 25 30
2 4 6 8 10 12 14 22 25 28 29
3 50
10 50 100
0 10 30 40
0 20 30
0 20 50
1 1
2
0 2 4 6 8 10
*/
