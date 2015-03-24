// 2-satisify problem
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
	// <SCC begin>
	int vfind[MAXN], findIdx;
	int stk[MAXN], stkIdx;
	int in_stk[MAXN], visited[MAXN];
	int contract[MAXN];
	int scc_cnt;
	// <SCC end>
	int scc(int u) {
	    in_stk[u] = visited[u] = 1;
	    stk[++stkIdx] = u, vfind[u] = ++findIdx;
	    int mn = vfind[u], v;
	    for(int i = 0; i < g[u].size(); i++) {
	    	v = g[u][i];
	        if(!visited[v])
	            mn = min(mn, scc(v));
	        if(in_stk[v])
	            mn = min(mn, vfind[v]);
	    }
	    if(mn == vfind[u]) {
	        do {
	            in_stk[stk[stkIdx]] = 0;
	            contract[stk[stkIdx]] = u;
	        } while(stk[stkIdx--] != u);
	        scc_cnt++;
	    }
	    return mn;
	}
	void addEdge(int u, int v) { // u -> v
		g[u].push_back(v);
	}
	int solvable() {
		for (int i = 0; i < n; i++)
			visited[i] = in_stk[i] = 0;
        scc_cnt = 1;
        for (int i = 0; i < n; i++) {
        	if (visited[i])	continue;
        	stkIdx = findIdx = 0;
        	scc(i);
        }
        
        for(int i = 0; i < n; i += 2)
			if(contract[i] == contract[i^1])
				return 0;
		return 1;
	}
	void computeChoice() {
		if (!solvable())
			return ;
		for (int i = 0; i < n; i += 2) {
			int val = 0;
			g[i].push_back(i^1);
			if (solvable())	val |= 1;
			g[i].pop_back();
			
			g[i^1].push_back(i);
			if (solvable())	val |= 2;
			g[i^1].pop_back();
			
			printf("%c", "-yn?"[val]);
		}
		puts("");
	}
	void init(int n) {
		this->n = n;
		for (int i = 0; i < n; i++)
			g[i].clear();
	}
} g;

// more than half of his or her opinions satisfied
// opinion <= 4
int main() {
	int n, m, cases = 0;
	char s[128];
	while (scanf("%d %d", &n, &m) == 2 && n) {
		g.init(2 * n);
		
		for (int i = 0; i < m; i++) {
			int vote[8], k, x;
			scanf("%d", &k);
			for (int j = 0; j < k; j++) {
				scanf("%d %s", &x, s);
				x--;
				vote[j] = x * 2 + (s[0] == 'y');
			}
			if (k <= 2) { // all satisfied
				for (int p = 0; p < k; p++)
					g.addEdge(vote[p]^1, vote[p]);
			} else { // one fail
				for (int p = 0; p < k; p++) {
					for (int q = 0; q < k; q++) {
						if (p == q)	continue;
						// p-th opinion fail
						g.addEdge(vote[p]^1, vote[q]);
					}
				}
			}
		}
		
		printf("Case %d: ", ++cases);
		if (!g.solvable()) {
			puts("impossible");
		} else {
			g.computeChoice();
		}
	}
	return 0;
}
