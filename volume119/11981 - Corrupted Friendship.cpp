#include <stdio.h> 
#include <vector>
#include <algorithm>
using namespace std;

vector<int> g[100005];
long long ret, cnt;
void dfs(int u) {
	cnt--;
	for(int i = 0; i < g[u].size(); i++)
		dfs(g[u][i]);
	ret += cnt;
}
int main() {
	int testcase, cases = 0, N, x, y;
	scanf("%d", &testcase);
	while(testcase--) {
		scanf("%d", &N);
		for(int i = 1; i <= N; i++)
			g[i].clear();
		for(int i = 1; i < N; i++) {
			scanf("%d %d", &x, &y);
			g[x].push_back(y);
		}
		ret = 0, cnt = N;
		dfs(1);
		printf("Case %d: %d %lld\n", ++cases, N - 1, ret);
	}
	return 0;
}
