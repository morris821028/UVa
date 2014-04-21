#include <stdio.h> 
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
vector< pair<int, int> > g[100005];
int dist[100005], used[100005], testcase = 0;
typedef pair<int, int> P;
struct cmp {
	bool operator() (const P a, const P b) const {
		if(a.first != b.first)
			return a.first > b.first;
		return a.second < b.second;
	}
}; 
int test;
int dfs(int st) {
	used[st] = 1;
	test++;
	for(int i = g[st].size() - 1; i >= 0; i--) {
		int u = g[st][i].first, w = g[st][i].second;
		if(used[u] == 0) {
			dfs(u);
		}
	}
}
int main() {
	int n, m, x, w;
	while(scanf("%d %d", &n, &m) == 2) {
		for(int i = 1; i <= n; i++)
			g[i].clear();
		for(int i = 1; i <= n; i++) {
			scanf("%d %d", &x, &w);
			g[x].push_back(make_pair(i, w));
			g[i].push_back(make_pair(x, w));
		}
		test = 0;
		dfs(1);
		if(test != n)
			while(1);
		else
			puts("YY");
	}
	return 0;
}
