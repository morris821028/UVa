#include <stdio.h> 
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

struct edge {
	int to, w;
	edge(int a = 0, int b = 0):
		to(a), w(b) {}
};
vector<edge> g[1024];
int dp[1024][1024], inq[1024][1024];
const int MAXE = 1000;
void solve(int source, int N) {
	for (int i = 0; i < N; i++)
		for (int j = 0; j <= MAXE; j++)
			dp[i][j] = 0x3f3f3f3f;
	queue<int> X, E;
	int u, v, w, e;
	dp[source][0] = 0;
	X.push(source), E.push(0);
	while (!X.empty()) {
		u = X.front(), X.pop();
		e = E.front(), E.pop();
		inq[u][e] = 0;
		if (e == MAXE)	continue;
		for (int i = 0; i < g[u].size(); i++) {
			v = g[u][i].to, w = g[u][i].w;
			if (dp[v][e+1] > dp[u][e] + w) {
				dp[v][e+1] = dp[u][e] + w;
				if (!inq[v][e+1]) {
					inq[v][e+1] = 1;
					X.push(v), E.push(e+1);
				}
			}
		}
	}
}
int main() {
	int N, M, S, Q;
	int x, y, w;
	while (scanf("%d %d %d", &N, &M, &S) == 3) {
		for (int i = 0; i < N; i++)
			g[i].clear();
		for (int i = 0; i < M; i++) {
			scanf("%d %d %d", &x, &y, &w);
			g[x].push_back(edge(y, w));
		}
		
		solve(S, N);
		
		scanf("%d", &Q);
		while (Q--) {
			scanf("%d", &x);
			double ret = 1e+30;
			int e = -1;
			if (x == S)
				ret = 0, e = 0;
			else {
				for (int i = 1; i <= MAXE; i++) {
					if (dp[x][i] != 0x3f3f3f3f) {
						if ((double)dp[x][i]/i < ret) {
							ret = (double)dp[x][i]/i;
							e = i;
						}
					}
				}
			}
			if (e == -1)
				puts("No Path");
			else
				printf("%.4lf %d\n", ret, e);
		}
		puts("");
	}
	return 0;
}
/*
3 2 0
0 1 100
1 2 200
3
0
1
2
 
5 5 0
0 1 3
1 2 4
2 3 5
2 4 6
4 3 1
2
2
3
*/
