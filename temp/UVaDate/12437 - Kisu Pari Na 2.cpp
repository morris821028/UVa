#include <stdio.h>
#include <algorithm>
#include <vector>
#include <string.h>
using namespace std;

const int MAXN = 32767;
vector<int> g[MAXN];
int dp_down[MAXN][2], dp_up[MAXN];
int visited[MAXN];
vector<int> VQ;
void dfs(int u) {
	VQ.push_back(u);
	visited[u] = 1;
	dp_down[u][0] = dp_down[u][1] = 0;
    for (int i = 0; i < g[u].size(); i++) {
    	int v = g[u][i];
    	if (visited[v])	continue;
    	dfs(v);
    	if (dp_down[v][0] + 1 > dp_down[u][1])
    		dp_down[u][1] = dp_down[v][0] + 1;
    	if (dp_down[u][1] > dp_down[u][0])
    		swap(dp_down[u][0], dp_down[u][1]);
    }
}
void dfs2(int u, int up) {
	visited[u] = 1;
    dp_up[u] = up;
    for (int i = 0; i < g[u].size(); i++) {
    	int v = g[u][i], nup;
    	if (visited[v])	continue;
    	if (dp_down[v][0]+1 != dp_down[u][0])
    		nup = dp_down[u][0];
    	else
    		nup = dp_down[u][1];
    	nup = max(nup, up) + 1;
    	dfs2(v, nup);
    }
}
int main() {
	int testcase, cases = 0;
    int n, m, q, x, y;
    scanf("%d", &testcase);
    while (testcase--) {
    	scanf("%d %d", &n, &m);
    	for (int i = 0; i < n; i++)
    		g[i].clear();
    	for (int i = 0; i < m; i++) {
    		scanf("%d %d", &x, &y);
    		x--, y--;
    		g[x].push_back(y);
    		g[y].push_back(x);
    	}
    	
    	int used[MAXN] = {};
    	int ret[MAXN];
    	for (int i = 0; i < n; i++)
    		visited[i] = 0;
    	for (int i = 0; i < MAXN; i++)
    		ret[i] = 0x3f3f3f3f;
    	for (int i = 0; i < n; i++) {
    		if (used[i] == 0) {
    			VQ.clear();
    			dfs(i);
    			for (int j = 0; j < VQ.size(); j++)
    				visited[VQ[j]] = 0;
    			dfs2(i, 0);
    			
    			int max_path = 0;
    			for (int j = 0; j < VQ.size(); j++) {
    				int u = VQ[j];
    				max_path = max(max_path, max(dp_down[u][0]+dp_down[u][1], dp_down[u][0] + dp_up[u]));
    				used[u] = 1;
    			}
    			for (int j = 1; j <= VQ.size(); j++) {
    				if (j <= max_path + 1)
    					ret[j] = min(ret[j], j - 1);
    				else
    					ret[j] = min(ret[j], max_path + (j - max_path - 1) * 2);
    			}
//    			printf("%d %d --\n", max_path, VQ.size());
    		}
    	}
    	
    	scanf("%d", &q);
    	
    	printf("Case %d:\n", ++cases);
    	for (int i = 0; i < q; i++) {
    		scanf("%d", &x);
    		if (ret[x] == 0x3f3f3f3f)
    			puts("impossible");
    		else
    			printf("%d\n", ret[x]);
    	}
    }
    return 0;
}
/*
99

10 8
1 2
2 3
3 4
4 5
3 6
6 7
8 9
9 10
7
1
2
3
4
5
6
7

2

2 1
1 2
3
1
2
3

5 4
1 2
2 3
2 4
2 5
2
3
2
*/ 

