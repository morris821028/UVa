#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <queue>
#include <algorithm>
#include <string.h>
using namespace std;
const int MAXN = 5005;
const int MAXL = ((MAXN*MAXN)>>5)+1;
class SCC {
public:
	int n;
	int mark[MAXL];
	// <SCC begin>
	int vfind[MAXN], findIdx;
	int stk[MAXN], stkIdx;
	int in_stk[MAXN], visited[MAXN];
	int contract[MAXN];
	int scc_cnt;
	// <SCC end>
	int GET(int x) {
		return mark[x>>5]>>(x&31)&1;
	}
	void SET(int x) {
		mark[x>>5] |= 1<<(x&31);
	}
	int scc(int u) {
	    in_stk[u] = visited[u] = 1;
	    stk[++stkIdx] = u, vfind[u] = ++findIdx;
	    int mn = vfind[u], v;
	    for(int i = 0; i < n; i++) {
	    	if (GET(u * n + i))
	    		continue;
	    	v = i;
	        if(!visited[v])
	            mn = min(mn, scc(v));
	        if(in_stk[v])
	            mn = min(mn, vfind[v]);
	    }
	    if(mn == vfind[u]) {
	        do {
	            in_stk[stk[stkIdx]] = 0;
	            contract[stk[stkIdx]] = scc_cnt;
	        } while(stk[stkIdx--] != u);
	        scc_cnt++;
	    }
	    return mn;
	}
	void addNotEdge(int u, int v) { // u -> v
		SET(u * n + v);
	}
	void solve() {
		for (int i = 0; i < n; i++)
			visited[i] = in_stk[i] = 0;
        scc_cnt = 0;
        for (int i = 0; i < n; i++) {
        	if (visited[i])	continue;
        	stkIdx = findIdx = 0;
        	scc(i);
        }
	}
	void init(int n) {
		this->n = n;
		memset(mark, 0, sizeof(mark));
	}
} g;

int main() {
	int N, M, D;
	int u, v;
	while (scanf("%d %d", &N, &M) == 2) {
		g.init(N);
		for (int i = 0; i < M; i++) {
			scanf("%d %d", &u, &v);
			u--, v--;
			g.addNotEdge(u, v);
		}
		scanf("%d", &D);
		
		g.solve();
		printf("%d\n", g.scc_cnt * D);
	}
	return 0;
}
