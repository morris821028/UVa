#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <algorithm>
#include <string.h>
using namespace std;
const int MAXN = 262144;
class TwoSat {
public:
    int n;
    vector<int> g[MAXN];
    int mark[MAXN], stk[MAXN];
    int stkIdx;
    void addEdge(int u, int v) { // u -> v
        g[u].push_back(v);
    }
    int dfs(int u) {
    	if (mark[u^1])
			return 0;
		if (mark[u])
			return 1;
		mark[u] = 1, stk[stkIdx++] = u;
		for (auto v : g[u]) {
			if (!dfs(v))
				return 0;
		}
		return 1;
	}
    int solvable() {
        for (int i = 0; i < n; i++)
            mark[i] = 0;
        for (int i = 0; i < n; i += 2) {
        	if (mark[i] == 0 && mark[i^1] == 0) {
        		stkIdx = 0;
        		if (dfs(i) == 0) {
        			if (i == 0)	//  seated on the same side as the bride 
        				return false;
        			while (stkIdx)
        				mark[stk[--stkIdx]] = 0;
        			if (dfs(i^1) == 0)
        				return false;
				}
			}
		}
		return true;
    }
    void findSolution() {
        if (!solvable()) {
        	puts("bad luck");
            return ;
        }
       
    	for (int i = 2; i < n; i += 2) {
    		printf("%d%c%c", i>>1, mark[i] ? 'w' : 'h', " \n"[i == n-2]);
		}
    }
    void init(int n) {
        this->n = n;
        for (int i = 0; i < n; i++)
            g[i].clear();
    }
} g;

int main() {
	int n, m;
	while (scanf("%d %d", &n, &m) == 2 && n+m) {
		g.init(2*n);
		
		for (int i = 0; i < m; i++) {
			int x, y;
			char xt[8], yt[8];
			scanf("%d%s %d%s", &x, &xt, &y, &yt);
			int u, v;
			u = x*2 + (xt[0] == 'h');
			v = y*2 + (yt[0] == 'h');
			g.addEdge(u^1, v);
			g.addEdge(v^1, u);
		}
		
		g.findSolution();
	}
	return 0;
}
/*
10  6
3h  7h
5w  3w
7h  6w
8w  3w
7h  3w
2w  5h
0 0
*/
