#include <bits/stdc++.h>
using namespace std;

const int MAXV = 128;
const int MAXE = 131072;
const int INF = 0x3f3f3f3f;
struct Edge {
    int to;
    int w;
    Edge *next;
};
Edge edge[MAXE], *adj[MAXV];
int e = 0;
void addEdge(int x, int y, int v)  {
    edge[e].to = y, edge[e].w = v;
    edge[e].next = adj[x], adj[x] = &edge[e++];
}

void solve(int n) {
	queue<int> Q;
	static int dist[MAXV], inq[MAXV], visited[MAXV];
	for (int i = 0; i <= n; i++)
		dist[i] = -INF, inq[i] = 0, visited[i] = 0;
	dist[1] = 0;
	Q.push(1);
	while (!Q.empty()) {
		int u = Q.front(); Q.pop();
		inq[u] = 0;
		visited[u]++;
		if (visited[u] > n) {
			puts("Unlimited!");
			return;
		}
		for (Edge *e = adj[u]; e != NULL; e = e->next) {
			int v = e->to, w = e->w;
			if (dist[v] < dist[u] + w) {
				dist[v] = dist[u] + w;
				if (!inq[v]) {
					inq[v] = 1;
					Q.push(v);
				} 
			}
		}
	}

	int ret = 0;
	for (int i = 1; i <= n; i++)
		ret = max(ret, dist[i]);
	printf("%d\n", ret);
}
int main() {
	int n, m;
	while (scanf("%d %d", &n, &m) == 2 && n) {
		e = 0;
    	for (int i = 1; i <= n; i++)
        	adj[i] = NULL;
        for (int i = 0; i < m; i++) {
        	int a, b, f;
        	scanf("%d %d %d", &a, &b, &f);
        	addEdge(a, b, f);
		}

		solve(n);
	}
	return 0;
}
/*
2 2
1 2 10
2 1 20
3 3
1 2 10
2 3 20
3 1 -30
0 0
*/
