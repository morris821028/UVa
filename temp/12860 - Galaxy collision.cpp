#include <stdio.h> 
#include <vector>
#include <algorithm>
#include <set>
#include <queue>
using namespace std;
vector<int> g[65536];
vector< pair<int, int> > X[524288];
void buildGraph(int x) {
	int d;
	for (int i = X[x].size() - 1; i >= 0; i--) {
		int y = X[x][i].first, u = X[x][i].second;
		for (int j = x - 5; j <= x + 5; j++) {
			if (j < 0)	continue;
			int st = (int)(lower_bound(X[j].begin(), X[j].end(), make_pair(y - 5, -1)) - X[j].begin());
			for (int k = st; k < X[j].size(); k++) {
				if (X[j][k].first > y + 5)	break;
				d = (x-j) * (x-j) + (X[j][k].first - y) * (X[j][k].first - y);
//				d = abs(x-j) + abs(X[j][k].first - y);
				if (d <= 25) {
					if (u != X[j][k].second) {
						g[u].push_back(X[j][k].second);
//						printf("%d -> %d\n", u + 1, X[j][k].second + 1);
					}
				}
			}
		}
	}
}
int visited[65536], dist[65536];
int bfs(int st) {
	queue<int> Q;
	int o[2] = {}, u, v;
	Q.push(st), dist[st] = 1, visited[st] = 1;
	while (!Q.empty()) {
		u = Q.front(), Q.pop();
		o[dist[u]&1]++;
		for (int i = 0; i < g[u].size(); i++) {
			v = g[u][i];
			if (visited[v] == 0)  {
				dist[v] = dist[u] + 1;
				visited[v] = 1;
				Q.push(v);
			}
		}
	}
	return min(o[0], o[1]);
}
int main() {
	int n, x, y;
	while (scanf("%d", &n) == 1) {
		set<int> S;
		for (int i = 0; i < n; i++) {
			scanf("%d %d", &x, &y);
			X[x].push_back(make_pair(y, i));
			S.insert(x);
			visited[i] = 0;
			g[i].clear();
		}
		for (set<int>::iterator it = S.begin();
			it != S.end(); it++)
			sort(X[*it].begin(), X[*it].end());
		for (set<int>::iterator it = S.begin();
			it != S.end(); it++)
			buildGraph(*it);
		int ret = 0;
		for (int i = 0; i < n; i++)
			if (visited[i] == 0)
				ret += bfs(i);
		printf("%d\n", ret);
		for (set<int>::iterator it = S.begin();
			it != S.end(); it++) {
			X[*it].clear();
		}
	}
	return 0;
}
/*
3
1 1
2 2
9 9
2
1 1
2 2
6
1 3
9 1
11 7
5 7
13 5
4 4
2
10 10
50 30
*/
