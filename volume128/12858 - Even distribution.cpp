#include <stdio.h> 
#include <set>
#include <queue> 
#include <vector>
#include <algorithm>
using namespace std;
int C[65536];
vector<int> g[65536];
int search(int n) {
	set<int> S[65536], UNION;
	queue<int> Q, P;
	int u, v, p, gg;
	for (int i = 0; i < n; i++)
		Q.push(i), P.push(C[i]), S[i].insert(C[i]), UNION.insert(C[i]);
	while (!Q.empty()) {
		u = Q.front(), Q.pop();
		p = P.front(), P.pop();
		for (int i = 0; i < g[u].size(); i++) {
			v = g[u][i];
			gg = __gcd(p, C[v]);
			if (S[v].find(gg) == S[v].end()) {
				S[v].insert(gg), UNION.insert(gg);
				Q.push(v), P.push(gg);
			}
		}
	}
	int ret = UNION.size();
	return ret;
}
int main() {
	int n, m, x, y;
	while (scanf("%d %d", &n, &m) == 2) {
		for (int i = 0; i < n; i++) {
			scanf("%d", &C[i]);
			g[i].clear();
		}
		for (int i = 0; i < m; i++) {
			scanf("%d %d", &x, &y);
			x--, y--;
			g[x].push_back(y);
			g[y].push_back(x);
		}
		printf("%d\n", search(n));
	}
	return 0;
}
/*
2 1
1 9
1 2
4 2
1 2 3 4
1 3
1 2
4 3
30 42 105 70
2 4
1 2
2 3
*/
