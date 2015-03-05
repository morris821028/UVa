#include <stdio.h> 
#include <queue>
#include <algorithm>
using namespace std;
#define INF 0x3f3f3f3f
#define MAXN (100000 + 5)
pair<int, int> dist[MAXN];
int inq[MAXN];
int cost[3][10];
void spfa(int from, int to) {
	for (int i = 0; i < MAXN; i++)
		dist[i] = make_pair(INF, INF);
	queue<int> Q;
	int u, v;
	pair<int, int> w;
	Q.push(from), dist[from] = make_pair(0, 0);
	while (!Q.empty()) {
		u = Q.front(), Q.pop();
		inq[u] = 0;
		if (dist[u].first > dist[to].first)
			continue;
		for (int i = 0; i < 10; i++) {
			v = u * 10 + i, w = make_pair(dist[u].first + cost[0][i], dist[u].second+1);
			if (v <= to && w < dist[v]) {
				dist[v] = w;
				if (!inq[v]) {
					inq[v] = 1, Q.push(v);
				}
			}
			v = u + i, w = make_pair(dist[u].first + cost[1][i], dist[u].second+1);
			if (v <= to && w < dist[v]) {
				dist[v] = w;
				if (!inq[v]) {
					inq[v] = 1, Q.push(v);
				}
			}
			v = u * i, w = make_pair(dist[u].first + cost[2][i], dist[u].second+1);
			if (v <= to && w < dist[v]) {
				dist[v] = w;
				if (!inq[v]) {
					inq[v] = 1, Q.push(v);
				}
			}
		}
	}
	printf("%d %d\n", dist[to].first, dist[to].second);
}
int main() {
	int from, to, cases = 0;
	while (scanf("%d %d", &from, &to) == 2) {
		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 10; j++)
				scanf("%d", &cost[i][j]);
		printf("Case %d: ", ++cases);
		spfa(from, to);
	}
	return 0;
}
