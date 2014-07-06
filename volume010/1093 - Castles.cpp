#include <stdio.h> 
#include <vector>
#include <algorithm>
using namespace std;

int N;
vector<int> g[105];
pair<int, int> D[105];
bool cmp(pair<int, int> a, pair<int, int> b) {
	if(a.first != b.first)
		return a.first > b.first;
	return a.second < b.second;
}
pair<int, int> dfs(int u, int p) {
	vector< pair<int, int> > branch;
	for(int i = 0; i < g[u].size(); i++) {
		int v = g[u][i];
		if(v != p)
			branch.push_back(dfs(v, u));
	}
	sort(branch.begin(), branch.end(), cmp);
	int a, b;
	a = D[u].first, b = D[u].second;
	for(int i = 0; i < branch.size(); i++) {
		a = max(a, b + branch[i].first);
		b += branch[i].second;
	}
	return make_pair(max(a, b), b);
	
}
int main() {
	int cases = 0, a, m, gg, u, v;
	while(scanf("%d", &N) == 1 && N) {
		for(int i = 1; i <= N; i++) {
			scanf("%d %d %d", &a, &m, &gg);	
			D[i] = make_pair(max(a, m+gg), m + gg);
		}
		for(int i = 1; i <= N; i++)
			g[i].clear();
		for(int i = 1; i < N; i++) {
			scanf("%d %d", &u, &v);
			g[u].push_back(v);
			g[v].push_back(u);
		}
		
		pair<int, int> ret = make_pair(0x3f3f3f3f, 0x3f3f3f3f);
		for(int i = 1; i <= N; i++) 
			ret = min(ret, dfs(i, -1));
		printf("Case %d: %d\n", ++cases, ret.first);
	}
	return 0;
}
