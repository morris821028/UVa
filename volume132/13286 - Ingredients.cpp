#include <bits/stdc++.h>
#include <stdint.h>
using namespace std;
const int MAXN = 16384;
const int MAXB = 16384;
struct Edge {
	int v, c, p;
	Edge(int v, int c = INT_MAX, int p = INT_MAX):
		v(v), c(c), p(p) {}
};
static unordered_map<string, int> R;
int indeg[MAXN];
pair<int, int> dp[MAXN];
vector<Edge> g[MAXN];
int str2int(string x) {
	int &v = R[x];
	if (v == 0) {
		v = R.size();
		g[v].clear(), dp[v] = {INT_MAX, INT_MAX};
	}
	return v;
}

int main() {
	int m, n;
	char s1[32], s2[32];
	while (scanf("%d%d", &m, &n) == 2) {
		R.clear();
		for (int i = 0; i < n; i++) {
			int c, p;
			scanf("%s%s%*s%d%d", s1, s2, &c, &p);
			int u = str2int(s1), v = str2int(s2);
			g[v].push_back(Edge(u, c, p)), indeg[u]++;
		}

		queue<int> Q;
		for (int i = 1; i <= R.size(); i++) {
			if (indeg[i] == 0)
				Q.push(i), dp[i] = {0, 0};
		}

		while (!Q.empty()) {
			int u = Q.front(); Q.pop();
			pair<int, int> t = dp[u];
			for (Edge e : g[u]) {
				if (--indeg[e.v] == 0)
					Q.push(e.v);
				if ((t.first + e.c < dp[e.v].first) || 
					(t.first + e.c == dp[e.v].first && t.second + e.p > dp[e.v].second))
					dp[e.v] = {t.first + e.c, t.second + e.p};
			}
		}
		static int64_t dp2[MAXB];
		{
			memset(dp2+1, -1, sizeof(dp2[0])*m);
			int mx_w = 0;
			for (int i = 1; i <= R.size(); i++) {
				int w = dp[i].first, v = dp[i].second;
				mx_w = min(mx_w+w, m);
				for (int j = mx_w; j >= w; j--) {
					if (dp2[j-w] >= 0)
						dp2[j] = max(dp2[j], dp2[j-w]+v);
				}
			}
		}
		
		int64_t ret_c = 0, ret_w = 0;
		for (int i = 1; i <= m; i++) {
			if (dp2[i] > ret_w)
				ret_w = dp2[i], ret_c = i;
		}
		printf("%lld\n%lld\n", ret_w, ret_c);
	}
	return 0;
}
