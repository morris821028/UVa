#include <bits/stdc++.h>
using namespace std;

const int MAXN = 305;
const int MAXP = 5;
struct Edge {
	int to, w;
	Edge(int to=0, int w=0): to(to), w(w) {}
};
struct State {
	int to, p;
	State(int to=0, int p=0): to(to), p(p) {}
};
vector<Edge> gt[MAXN], gp[MAXN];

int main() {
	int testcase;
	scanf("%d", &testcase);
	while (testcase--) {
		int n, m, p, st, ed;
		scanf("%d", &n);
		scanf("%d %d", &st, &ed);
		scanf("%d", &p);
		
		for (int i = 0; i <= n; i++)
			gt[i].clear(), gp[i].clear();
			
		scanf("%d", &m);
		for (int i = 0; i < m; i++) {
			int u, v, w;
			scanf("%d %d %d", &u, &v, &w);
			gt[u].push_back(Edge(v, w));
			gt[v].push_back(Edge(u, w));
		}
		scanf("%d", &m);
		for (int i = 0; i < m; i++) {
			int u, v, w;
			scanf("%d %d %d", &u, &v, &w);
			gp[u].push_back(Edge(v, w));
			gp[v].push_back(Edge(u, w));
		}
		
		int dist[MAXN][MAXP], inq[MAXN][MAXP] = {};
		int ret = 0x3f3f3f3f;
		memset(dist, 0x3f, sizeof(dist));
		dist[st][0] = 0;
		queue<State> Q;
		Q.push(State(st, 0));
		while (!Q.empty()) {
			State u = Q.front();
			Q.pop();
			inq[u.to][u.p] = 0;
			const int c = dist[u.to][u.p];
			if (u.to == ed && c < ret)
				ret = c;
			if (dist[u.to][u.p] >= ret)
				continue;
			for (auto e : gt[u.to]) {
				if (dist[e.to][u.p] > c + e.w) {
					dist[e.to][u.p] = c + e.w;
					if (!inq[e.to][u.p]) {
						inq[e.to][u.p] = 1;
						Q.push(State(e.to, u.p));
					}
				}
			}
			if (u.p < p) {
				for (auto e : gp[u.to]) {
					if (dist[e.to][u.p+1] > c+ e.w) {
						dist[e.to][u.p+1] = c + e.w;
						if (!inq[e.to][u.p+1]) {
							inq[e.to][u.p+1] = 1;
							Q.push(State(e.to, u.p+1));
						}
					}
				}
			}
		}
		printf("%d\n", ret);
	}
	return 0;
}

