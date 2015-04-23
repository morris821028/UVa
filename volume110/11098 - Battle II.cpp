// SCC, DAG, greedy
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <queue>
#include <algorithm>
#include <string.h>
using namespace std;
const int MAXN = 1024;
class SCC {
public:
	int n;
	vector<int> g[MAXN], dag[MAXN];
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
	            contract[stk[stkIdx]] = scc_cnt;
	        } while(stk[stkIdx--] != u);
	        scc_cnt++;
	    }
	    return mn;
	}
	void addEdge(int u, int v) { // u -> v
		g[u].push_back(v);
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
	void make_DAG() {
		int x, y;
		for (int i = 0; i < n; i++) {
			x = contract[i];
			for (int j = 0; j < g[i].size(); j++) {
				y = contract[g[i][j]];
				if (x != y)
					dag[x].push_back(y);
			}
		}
		for (int i = 0; i < scc_cnt; i++) {
			sort(dag[i].begin(), dag[i].end());
			dag[i].resize(unique(dag[i].begin(), dag[i].end()) - dag[i].begin());
		}
	}
	void init(int n) {
		this->n = n;
		for (int i = 0; i < n; i++)
			g[i].clear(), dag[i].clear();
	}
} g;

int X[MAXN], Y[MAXN], E[MAXN], R[MAXN];
void greedy() {
	int m = g.scc_cnt, n = g.n;
	int cost[MAXN], scc_id[MAXN], pick[MAXN] = {};
	for (int i = 0; i < m; i++)
		cost[i] = 0x3f3f3f3f, scc_id[i] = -1;
	for (int i = 0; i < n; i++) {
		if (cost[g.contract[i]] > E[i])
			cost[g.contract[i]] = E[i], scc_id[g.contract[i]] = i;
	}
	
	int indeg[MAXN]	= {};
	vector<int> topo;
	queue<int> Q;
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < g.dag[i].size(); j++) {
			indeg[g.dag[i][j]]++;
		}
	}
		
	// greedy, let reta / retb = minimum value
	// if (reta / retb) > (reta + cost) / (retb + 1)
	long long reta = 0, retb = 0; // min average cost = total cost / #bomb
	vector< pair<int, int> > candidate;
	for (int i = 0; i < m; i++) {
		if (indeg[i] == 0) {
			reta += cost[i], retb++;
			pick[i] = 1;
		} else {
			candidate.push_back(make_pair(cost[i], i));
		}
	}
	sort(candidate.begin(), candidate.end()); 
	for (int i = 0; i < candidate.size(); i++) {
		long long c = candidate[i].first;
		if (reta * (retb + 1) > (reta + c) * retb) {
			reta += c, retb++;
			pick[candidate[i].second] = 1;
		}
	}
	
	// topo
	for (int i = 0; i < m; i++)
		if (indeg[i] == 0)	Q.push(i);
	while (!Q.empty()) {
		int u = Q.front(), v;
		Q.pop();
		topo.push_back(u);
		for (int i = 0; i < g.dag[u].size(); i++) {
			v = g.dag[u][i];
			if (--indeg[v] == 0)
				Q.push(v);
		}
	}
	
	// make order with fire rule
	int topo_r[MAXN] = {};
	vector< pair<int, int> > ret;
	for (int i = 0; i < topo.size(); i++) {
		topo_r[topo[i]] = i;
	}
	for (int i = 0; i < m; i++) {
		if (pick[i])
			ret.push_back(make_pair(topo_r[i], scc_id[i]));
	}
	sort(ret.begin(), ret.end());
	
	for (int i = ret.size() - 1; i >= 0; i--)
		printf(" %d", ret[i].second);
	puts("");
//	printf("%lld / %lld\n", reta, retb);
}
int main() {
	int testcase, cases = 0;
	int n;
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%d", &n);
		for (int i = 0; i < n; i++)
			scanf("%d %d %d %d", &X[i], &Y[i], &R[i], &E[i]);
		
		g.init(n);	
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				if (i == j)
					continue;
				long long dist = (long long)(X[i] - X[j]) * (X[i] - X[j]) + (long long)(Y[i] - Y[j]) * (Y[i] - Y[j]);
				long long r = (long long)(R[i] + E[i] + R[j]) * (R[i] + E[i] + R[j]);
				if (dist <= r) 
					g.addEdge(i, j);
			}
		}
		
		g.solve();
		g.make_DAG();
		
		printf("Case #%d:", ++cases);
		greedy();
	}
	return 0;
}
/*
1

3
4 7 2 2
8 5 1 0
3 -3 1 1

1

7
24 1 4 7
38 33 4 3
13 13 2 0
34 1 0 0
6 25 5 4
1 14 3 7
30 35 1 6

*/
