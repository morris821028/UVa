#include <stdio.h>
#include <math.h>
#include <string.h>
#include <vector>
#include <algorithm>
using namespace std;

vector<int> g[128];
vector< pair<int, int> > Q[128];// query pair, v - input index.
int visited[128], F[128], depth[128];
int LCA[128];//input query answer buffer.
int findF(int x) {
    return F[x] == x ? x : (F[x]=findF(F[x]));
}
void tarjan(int u, int p, int d) {// tree.
    F[u] = u, depth[u] = d;
    for(int i = 0; i < g[u].size(); i++) {//son node.
		int v = g[u][i];
    	if(v == p)	continue;
        tarjan(v, u, d+1);
        F[findF(v)] = u;
    }
    visited[u] = 1;
    for(int i = 0; i < Q[u].size(); i++) {
        if(visited[Q[u][i].second]) {
            LCA[Q[u][i].first] = findF(Q[u][i].second);
        }
    }
}
int main() {
	int N, A, B, C, x, y;
	while(scanf("%d %d %d %d", &N, &A, &B, &C) == 4) {
		for(int i = 1; i <= N; i++)
			g[i].clear();
		for(int i = 1; i < N; i++) {
			scanf("%d %d", &x, &y);
			g[x].push_back(y);
			g[y].push_back(x);
		}
		
		for(int i = 1; i <= N; i++)
            visited[i] = 0, Q[i].clear();
        Q[B].push_back(make_pair(0, C));
        Q[C].push_back(make_pair(0, B));
        tarjan(A, -1, 0);
        
		double ret = 0;
		int lca = LCA[0];
		int lb = depth[B] - depth[lca], lc = depth[C] - depth[lca];
		if(lb == 0)	
			ret = 1;
		else if(lc == 0)
			ret = 0;
		else
			ret = lc / (double)(lb + lc);
		printf("%lf\n", ret);
	}
	return 0;
}
