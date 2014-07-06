#include <stdio.h>
#include <vector>
#include <queue>
#include <algorithm>
#include <string.h>
using namespace std;
#define MAXN 20005
vector<int> g[MAXN];
int vfind[MAXN], findIdx;
int stk[MAXN], stkIdx;
int in_stk[MAXN], visited[MAXN];
int contract[MAXN], scc_cnt = 0;
int scc(int nd) {
    in_stk[nd] = visited[nd] = 1;
    stk[++stkIdx] = nd;
    vfind[nd] = ++findIdx;
    int mn = vfind[nd];
    for(int i = 0; i < g[nd].size(); i++) {
        if(!visited[g[nd][i]])
            mn = min(mn, scc(g[nd][i]));
        if(in_stk[g[nd][i]])
            mn = min(mn, vfind[g[nd][i]]);
    }
    if(mn == vfind[nd]) {
    	scc_cnt++;
        do {
            in_stk[stk[stkIdx]] = 0;
            contract[stk[stkIdx]] = scc_cnt;
        } while(stk[stkIdx--] != nd);
    }
    return mn;
}
int main() {
	int testcase, n, m, x, y;
	scanf("%d", &testcase);
	while(testcase--) {
		scanf("%d %d", &n, &m);
		for(int i = 0; i <= n; i++)
			g[i].clear();
		for(int i = 0; i < m; i++) {
			scanf("%d %d", &x, &y);
			g[x].push_back(y);
		}
		// SCC
		scc_cnt = 0;
        memset(visited, 0, sizeof(visited));
        memset(in_stk, 0, sizeof(in_stk));
        for(int i = 1; i <= n; i++) {
            if(!visited[i]) {
                findIdx = stkIdx = 0;
                scc(i);
            }
        }
        
        int indeg[MAXN] = {}, outdeg[MAXN] = {};
        for(int i = 1; i <= n; i++) {
        	int u = contract[i], v;
        	for(int j = 0; j < g[i].size(); j++) {
        		v = contract[g[i][j]];
        		if(u != v)
        			outdeg[u]++, indeg[v]++;
        	}
        }
        int IN = 0, OUT = 0;
        for(int i = 1; i <= scc_cnt; i++) {
        	if(indeg[i] == 0)
        		IN++;
        	if(outdeg[i] == 0)
        		OUT++;
        }
        if(scc_cnt == 1)
        	puts("0");
        else
        	printf("%d\n", max(IN, OUT));
	}
	return 0;
}
