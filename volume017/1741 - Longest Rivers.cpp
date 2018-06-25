#include <bits/stdc++.h> 
using namespace std;
const int MAXN = 500005;
const int MAXM = 500005;
const int MAXS = 16;

int main() {
	int n, m;
	static char name[MAXN][MAXS];
	static int c[MAXN], d[MAXN];
	static int cc[MAXN], cd[MAXN];

	while (scanf("%d %d", &n, &m) == 2) {
		vector<vector<int>> g(m+1);
		vector<int> gn(m+1, 0);
		
		priority_queue<pair<int64_t, int>> S;
		for (int i = 1; i <= n; i++) {
			scanf("%s %d %d", name[i], &c[i], &d[i]);
			g[c[i]].push_back(-i);
			gn[c[i]]++;
			S.push({-d[i], c[i]});
		}
		
		for (int i = 1; i <= m; i++) {
			scanf("%d %d", &cc[i], &cd[i]);
			g[cc[i]].push_back(i);
			gn[cc[i]]++;
		}
		
		vector<pair<int64_t, int>> Q, A;
		Q.push_back({0, 0});
		while (!Q.empty()) {
			auto e = Q.back(); Q.pop_back();
			int u = e.second;
			int64_t dist = e.first;
			for (int i = 0; i < g[u].size(); i++) {
				if (g[u][i] < 0)
					A.push_back({dist + d[-g[u][i]], -g[u][i]});
				else
					Q.push_back({dist + cd[g[u][i]], g[u][i]});
			}
		}
		sort(A.begin(), A.end());
		
		static int ret[MAXN];
		vector<int64_t> cmn(m+1, 1e+18);
		for (int i = 0, sm = 0; i < n; i++) {
			while (!S.empty() && -S.top().first <= A[i].first) {
				auto e = S.top(); S.pop();
				int u = e.second;
				int64_t dist = -e.first;
				cmn[u] = min(cmn[u], dist);
				gn[u]--;
				if (gn[u] > 0 || u == 0)
					sm++;
				else
					S.push({-(cmn[u]+cd[u]), cc[u]});
			}
			ret[A[i].second] = n-sm+1;
		}
		
		for (int i = 1; i <= n; i++)
			printf("%s %d\n", name[i], ret[i]);
	}
	return 0;
}
/*
6  2
PaSak  0  513
Nan  2  675
Yom  2  700
Wang  1  335
Ping  1  305
ThaChin  0  765
0  353
0  65
*/
