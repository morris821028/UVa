#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <queue>
#include <algorithm>
#include <string.h>
using namespace std;
const int MAXN = 131072;
const int MAXQ = 131072;
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
	            contract[stk[stkIdx]] = u;
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
} scc;

class LCAoffline {
public:
	int visited[MAXN], visited2[MAXN], depth[MAXN];
	vector<int> tree[MAXN];
	vector< pair<int, int> > Q[MAXN];	// query pair, input index - node
	int LCA[MAXQ]; 						// [#query] input query answer buffer.
	int n;
	int parent[MAXN], weight[MAXN];
	int findp(int x) {
	    return parent[x] == x ? x : (parent[x] = findp(parent[x]));
	}
	int joint(int x, int y) {
	    x = findp(x), y = findp(y);
	    if(x == y)
	        return 0;
	    if(weight[x] > weight[y])
	        weight[x] += weight[y], parent[y] = x;
	    else
	        weight[y] += weight[x], parent[x] = y;
	    return 1;
	}
	void tarjan(int u, int p, int dep) {// rooted-tree.
	    parent[u] = u, visited2[u] = 1, depth[u] = dep;
	    for(int i = 0; i < tree[u].size(); i++) {//son node.
	        int v = tree[u][i];
	        if(v == p || visited2[v])	continue;
	        tarjan(v, u, dep+1);
	        parent[findp(v)] = u;
	    }
	    visited[u] = 1;
	    for(int i = 0; i < Q[u].size(); i++) {
	        if(visited[Q[u][i].second]) {
	            LCA[Q[u][i].first] = findp(Q[u][i].second);
	        }
	    }
	}
	void addEdge(int x, int y) {
		tree[x].push_back(y);
        tree[y].push_back(x);
	}
	void addQuery(int x, int y, int id) {
		Q[x].push_back(make_pair(id, y));
		Q[y].push_back(make_pair(id, x));
		LCA[id] = -1;
	}
	void init(int n) {
		this->n = n;
		for (int i = 0; i < n; i++) {
			tree[i].clear(), Q[i].clear();
			visited[i] = visited2[i] = 0;
			parent[i] = i, weight[i] = 1;
		}
	}
} lca;

class DisjointSet {
public:
	int parent[MAXN], weight[MAXN];
	int findp(int x) {
	    return parent[x] == x ? x : (parent[x] = findp(parent[x]));
	}
	int joint(int x, int y) {
	    x = findp(x), y = findp(y);
	    if(x == y)
	        return 0;
	    if(weight[x] > weight[y])
	        weight[x] += weight[y], parent[y] = x;
	    else
	        weight[y] += weight[x], parent[x] = y;
	    return 1;
	}
	void init(int n) {
		for (int i = 0; i < n; i++)
			parent[i] = i, weight[i] = 1;
	}
} disjoint_set;

int N, Q, F[MAXN], A[MAXN], B[MAXN];
int onCycle[MAXN], distCycle[MAXN], szCycle[MAXN];
int main() {
	while (scanf("%d", &N) == 1) {
		for (int i = 0; i < N; i++) {
			scanf("%d", &F[i]);
			F[i]--;
		}
				
		scanf("%d", &Q);
		for (int i = 0; i < Q; i++) {
			scanf("%d %d", &A[i], &B[i]);
			A[i]--, B[i]--;
		}
		
		scc.init(N);
		for (int i = 0; i < N; i++)
			scc.addEdge(i, F[i]);
		scc.solve();
		scc.make_DAG();
	
		int v_pt = N; // virtual point
		lca.init(N+1);
		for (int i = 0; i < N; i++) {
			if (scc.dag[scc.contract[i]].size() == 0) // outdegree = 0
				lca.addEdge(v_pt, i);
			else
				lca.addEdge(F[i], i);
		}
		for (int i = 0; i < Q; i++)
			lca.addQuery(A[i], B[i], i);
		lca.tarjan(v_pt, -1, 0);
		
//		for (int i = 0; i < Q; i++)
//			printf("LCA(%d, %d) = %d\n", A[i], B[i], lca.LCA[i]);
		
		int cid = 0;
		disjoint_set.init(N+1);
		for (int i = 0; i < N; i++) {
			if (scc.dag[scc.contract[i]].size() != 0)
				disjoint_set.parent[i] = F[i];
			onCycle[i] = -1;
		}
		
		for (int i = 0; i < N; i++) {
			if (scc.contract[i] != i && onCycle[i] == -1) {
				szCycle[cid] = 0;
				for (int u = i, d = 0; onCycle[u] == -1; u = F[u], d++, szCycle[cid]++) {
					onCycle[u] = cid, distCycle[u] = d;
				}
				cid++;
			}
		}
		
		for (int i = 0; i < Q; i++) {
			int u = A[i], v = B[i], c = lca.LCA[i];
			int dist = lca.depth[u] + lca.depth[v] - 2 * lca.depth[c];
			if (lca.LCA[i] == v_pt) {
				int pu = disjoint_set.findp(u);
				int pv = disjoint_set.findp(v);
				if (onCycle[pu] == onCycle[pv]) {
					int du = distCycle[pu], dv = distCycle[pv], dist_puv;
					if (du < dv)	
						swap(du, dv);
					dist_puv = min(du - dv, szCycle[onCycle[pu]] - (du - dv));
					dist = dist - 2 + dist_puv;
					printf("%d\n", dist);
				} else {
					puts("-1");
				}
			} else {
				printf("%d\n", dist);
			}
		}
			
	}
	return 0;
}
/*
3
2 1 2
3
1 2
1 3
1 1

7
2 1 4 5 3 5 6
5
1 3
4 7
7 4
6 2
2 1

10
3 5 9 5 10 9 3 7 4 6
10
5 5
3 5
2 5
1 8
10 8
1 1
3 4
8 5
3 5
8 10

10
8 10 3 7 6 4 9 4 9 3
10
4 6
8 6
10 7
4 9
8 2
4 8
1 7
5 9
4 10
10 10
*/
