// 2-satisify problem, solution
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <algorithm>
#include <string.h>
using namespace std;
const int MAXN = 262144;
class TwoSat {
public:
    int n, mark[MAXN];
    int stk[MAXN], stkIdx;
    vector<int> g[MAXN];
    int assign[MAXN];
    void addEdge(int u, int v) { // u -> v
        g[u].push_back(v);
    }
    int dfs(int u) {
        if (mark[u^1])  return 0;
        if (mark[u])    return 1;
        mark[u] = 1, stk[++stkIdx] = u;
        for (int i = 0; i < g[u].size(); i++) {
            int v = g[u][i];
            if (!dfs(v))
                return false;
        }
        return true;
    }
    int solvable() {
    	for (int i = 0; i < n; i += 2) {
    		if (mark[i] == 1 && mark[i+1] == 1) 
        		return 0;
        	if (assign[i]) {
        		stkIdx = -1;
        		if (!dfs(i))
        			return 0;
        	}
        	if (assign[i+1]) {
        		stkIdx = -1;
        		if (!dfs(i+1))
        			return 0;
        	}
    	}
        for(int i = 0; i < n; i += 2) {
            if (mark[i] == 0 && mark[i+1] == 0) {
                stkIdx = -1;
                if (!dfs(i)) {
                    while (stkIdx >= 0)
                        mark[stk[stkIdx]] = 0, stkIdx--;
                    if (!dfs(i+1))
                        return 0;
                }
            }
        }
        return 1;
    }
    void init(int n) {
        this->n = n;
        for (int i = 0; i < n; i++)
            g[i].clear(), mark[i] = 0, assign[i] = 0;
    }
} g;

struct Core {
	int type;
	int V[4], L[4];
	void read() {
		if (type == 0) {
			scanf("%d %d", &L[0], &L[1]);
			scanf("%d %d", &V[0], &V[1]);
			L[0]--, L[1]--;
			L[0] *= 2, L[1] *= 2;
			g.assign[L[0]^V[0]] = 1;
			g.assign[L[1]^V[1]] = 1;
		} else {
			scanf("%d %d", &L[0], &L[1]);
			scanf("%d %d", &V[0], &V[1]);
			scanf("%d %d", &L[2], &L[3]);
			scanf("%d %d", &V[2], &V[3]);
			L[0]--, L[1]--,	L[2]--, L[3]--;
			L[0] *= 2, L[1] *= 2;
			L[2] *= 2, L[3] *= 2;
			g.addEdge(L[0]^(!V[0]), L[2]^V[2]);
			g.addEdge(L[1]^(!V[1]), L[2]^V[2]);
			g.addEdge(L[0]^(!V[0]), L[3]^V[3]);
			g.addEdge(L[1]^(!V[1]), L[3]^V[3]);
			g.addEdge(L[2]^(!V[2]), L[0]^V[0]);
			g.addEdge(L[3]^(!V[3]), L[0]^V[0]);
			g.addEdge(L[2]^(!V[2]), L[1]^V[1]);
			g.addEdge(L[3]^(!V[3]), L[1]^V[1]);
		}
	}
};
int main() {
	int testcase;
	scanf("%d", &testcase);
	while (testcase--) {
		int N, S, D;
		scanf("%d %d %d", &N, &S, &D);
		g.init(N*2);
		Core SC[1024], DC[1024];
		for (int i = 0; i < S; i++) {
			SC[i].type = 0;
			SC[i].read();
		}
		for (int i = 0; i < D; i++) {
			DC[i].type = 1;
			DC[i].read();
		}
		
		printf("%s\n", g.solvable() ? "Yes" : "No");
	}
	return 0;
}
