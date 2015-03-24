#include <stdio.h> 
#include <string.h>
#include <vector>
#include <algorithm>
#include <assert.h>
#include <queue>
#include <map>
using namespace std;
const int MAXNT = 32767;
vector<int> route[MAXNT];
int NTc[MAXNT], NT;
struct Edge {
	int to, w, label;
	Edge(int a = 0, int b = 0, int c = 0):
		to(a), w(b), label(c) {}
};
vector<Edge> g[MAXNT];
map< pair<int, int>, int> Rid;
int getId(pair<int, int> x) {
	if (Rid.count(x))
		return Rid[x];
	int &r = Rid[x];
	return r = Rid.size();
}

pair<int, int> dist[MAXNT];
int pre[MAXNT][2], inq[MAXNT];
void spfa(int st) {
	memset(dist, 63, sizeof(dist));
	memset(pre, -1, sizeof(pre));
	memset(inq, 0, sizeof(inq));
	
	int u, v;
	queue<int> Q;
	
	Q.push(st), dist[st] = pair<int, int>(0, 0);
	while (!Q.empty()) {
		u = Q.front(), Q.pop();
		inq[u] = 0;
		for (int i = 0; i < g[u].size(); i++) {
			v = g[u][i].to;
			if (dist[v] > pair<int, int>(dist[u].first + g[u][i].w, dist[u].second+1)) {
				dist[v] = pair<int, int>(dist[u].first + g[u][i].w, dist[u].second+1);
				pre[v][0] = u, pre[v][1] = g[u][i].label;
				if (!inq[v]) {
					inq[v] = 1, Q.push(v);
				}
			}
		}
	}
}
void solve(int N, int A[]) {
	for (int i = 0; i < MAXNT; i++) 
		g[i].clear();
	Rid.clear();
	
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < NT; j++) {
			int st = i, ed = i;
			for (int k = 0; k < route[j].size(); k++) {
				if (ed+1 < N && route[j][k] == A[ed+1])
					ed++;
				int u = getId(pair<int, int>(st, route[j][0]));
				int v = getId(pair<int, int>(ed, route[j][k]));
				g[u].push_back(Edge(v, NTc[j], j));
//				printf("[%d] %d -> %d\n", j, u, v);
				if (ed == N)
					break;
			}
		}
	}
	
	int st = getId(pair<int, int>(0, A[0]));
	int ed = getId(pair<int, int>(N-1, A[N-1]));
	spfa(st);
	
	vector<int> buy;
	for (int i = ed; i >= 0; i = pre[i][0])
		buy.push_back(pre[i][1]);
	printf("Cost = %d\n", dist[ed].first);
	printf("  Tickets used:");
	for (int i = (int) buy.size() - 2; i >= 0; i--)
		printf(" %d", buy[i]+1);
	puts("");
}
int main() {
	int N, Q, cases = 0;
	int A[MAXNT];
	while (scanf("%d", &NT) == 1 && NT) {
		for (int i = 0; i < NT; i++) {
			int m, x;
			scanf("%d %d", &NTc[i], &m);
			route[i].clear();
			for (int j = 0; j < m; j++) {
				scanf("%d", &x);
				route[i].push_back(x);
			}
		}
		
		scanf("%d", &Q), ++cases;
		for (int i = 0; i < Q; i++) {
			scanf("%d", &N);
			for (int j = 0; j < N; j++)
				scanf("%d", &A[j]);
			printf("Case %d, Trip %d: ", cases, i+1);
			solve(N, A);
		}
	}
	return 0;
} 
/*
3 
225 3 1 3 4 
200 2 1 2 
50 2 2 3 
3
2 1 3 
1 1
0

3 
100 2 2 4 
100 3 1 4 3 
200 3 1 2 3 
2 
3 1 4 3 
3 1 2 4 
0
*/
