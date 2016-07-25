#include <bits/stdc++.h>
using namespace std;
struct Edge {
	int u, v;
	int ul, ur, vl, vr;
};
const int MAXV = 524288;
const int INF = 2000000000;
Edge e[MAXV];
map<int, int> R[MAXV];
vector< pair<int,int> > g[MAXV];
int V, E, W, S, T;
set< pair<int, int> > pQ;
int dist[MAXV];
inline int update(int u, int d) {
	if (dist[u] <= d || d >= W)
		return 0;
	if (dist[u] != INF)
		pQ.erase(pQ.find(make_pair(dist[u], u)));
	dist[u] = d;
	pQ.insert(make_pair(dist[u], u));
	return 1;
}
int bfs(int st, int ed, int n) {
	for (int i = 0; i <= n; i++)
		dist[i] = INF;
	pQ.clear();
	pair<int, int> u, v;
	pQ.insert(make_pair(0, 1)), dist[1] = 0;
	while (!pQ.empty()) {
		u = *pQ.begin(), pQ.erase(pQ.begin());
		if (u.second == ed)
			return u.first;
		for (auto e : g[u.second])
			update(e.first, dist[u.second] + e.second);
	}
	return dist[ed];
}
int main() {
	int cases = 0;
	while (scanf("%d %d %d", &V, &E, &W) == 3 && V) {
		scanf("%d %d", &S, &T);
		for (int i = 0; i < E; i++) {
			scanf("%d %d %d %d %d %d", 
				&e[i].u, &e[i].v, &e[i].ul, &e[i].ur, &e[i].vl, &e[i].vr);
		}
		for (int i = 0; i < E; i++) {
			R[e[i].u][e[i].ul] = 0;
			R[e[i].v][e[i].vr] = 0;
		}
		R[1][0] = 0;
		R[S][T] = 0;
		// -- relabel
		int vid = 0;
		for (int i = 1; i <= V; i++) {
			int last_time = -1;
			for (auto &e : R[i]) {
				e.second = ++vid;
				if (last_time != -1) { // keep in this node, make them run in order.
					g[vid-1].push_back(make_pair(vid, e.first - last_time));
				}
				last_time = e.first;
			}
		}
		// -- build graph
		for (int i = 0; i < E; i++) {
			int tu = R[e[i].u][e[i].ul];
			int tv = R[e[i].v][e[i].vr];
			int cc = (e[i].ur - e[i].ul) + (e[i].vr - e[i].vl);
			g[tu].push_back(make_pair(tv, cc));
		}
		
		printf("Plant %d: %d\n", ++cases, max(0, W-bfs(R[1][0], R[S][T], vid)));
		
		for (int i = 1; i <= vid; i++)
			g[i].clear();
	}
	return 0;
}
/*
3 2 50
2 50
1 3 0 10 20 30
3 2 10 20 30 40

3 6 50
2 50
1 2 0 10 20 30
1 2 5 6 9 11
2 3 13 15 25 28
3 3 32 33 40 45
3 1 30 31 39 40
1 2 41 42 48 49
5 13 20
3 1000
3 3 41 41 999 1000
3 3 39 40 1000 1000
5 4 25 25 30 30
1 2 2 2 6 6
1 2 1 1 8 8
2 2 7 7 13 13
2 2 8 8 15 15
2 3 14 14 20 20
2 3 16 16 20 20
4 3 30 30 40 40
4 3 32 32 41 41
3 5 21 21 25 25
3 5 22 22 25 25
3 3 50
3 30
1 2 5 10 15 25
2 3 20 20 30 30
2 3 25 25 30 30
*/
