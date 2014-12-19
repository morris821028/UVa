#include <stdio.h>
#include <vector>
#include <queue>
#include <algorithm> 
using namespace std;
#define MAXN 32767
vector< pair<int, int> > g[MAXN];
int dist1[MAXN], dist2[MAXN];
void spfa(int st, int ed, int dist[]) {
	static int inq[MAXN];
	queue<int> Q;
	int u, v, w;
	dist[st] = 0, Q.push(st);
	while (!Q.empty()) {
		u = Q.front(), Q.pop();
		inq[u] = 0;
		for (int i = 0; i < g[u].size(); i++) {
			v = g[u][i].first, w = g[u][i].second;
			if (dist[v] > dist[u] + w) {
				dist[v] = dist[u] + w;
				if (!inq[v])
					inq[v] = 1, Q.push(v);
			}
		}
	}
}
int main() {
	int n, m;
	int x, y, w;
	while (scanf("%d %d", &n, &m) == 2) {
		for (int i = 0; i < n; i++)
			g[i].clear();
		for (int i = 0; i < m; i++) {
			scanf("%d %d %d", &x, &y, &w);
			g[x].push_back(make_pair(y, w));
			g[y].push_back(make_pair(x, w));
		}
		
		for (int i = 0; i < n; i++)
			dist1[i] = dist2[i] = 0x3f3f3f3f;
		spfa(0, n-1, dist1);
		spfa(n-1, 0, dist2);
	
		int sp = dist1[n - 1], ret = 0;
		for (int i = 0; i < n; i++) {
			x = i;
			for (int j = 0; j < g[i].size(); j++) {
				y = g[i][j].first, w = g[i][j].second;
				if (dist1[x] + w + dist2[y] == sp)
					ret += w;
			}
		}
		printf("%d\n", ret * 2);
	}
	return 0;
}
/*
10 15
0 1 580
1 4 90
1 4 90
4 9 250
4 2 510
2 7 600
7 3 200
3 3 380
3 0 150
0 3 100
7 8 500
7 9 620
9 6 510
6 5 145
5 9 160
4 7
0 1 1
0 2 2
0 3 10
0 3 3
1 3 2
2 3 1
1 1 1
*/
